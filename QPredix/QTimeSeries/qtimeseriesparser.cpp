#include "qtimeseriesparser.h"
#include "qtimeseriescommands.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDateTime>

QTimeSeriesParser::QTimeSeriesParser()
{

}

QByteArray QTimeSeriesParser::formRequestJson(QList<QTimeSeriesTag> tags)
{
    QByteArray rTags;
    rTags.append("{\"tags\":[");

    QByteArray lTag;
    for (QTimeSeriesTag tag : tags) {
        lTag.clear();
        lTag.append("{");

        lTag.append("\"name\":\"").append(tag.name()).append("\",");

        lTag.append("\"suppressGroupByType\":").append(tag.suppressGroupByType()).append(",");

        lTag.append("\"filters\":{");
        QByteArray lHost("\"host\":[");

        //attributes
        lTag.append("\"attributes\": {");
        for (QString host : tag.attributes()) {
            lHost.append(host).append(",");
        }
        lHost.remove(lHost.size()-1, 1);
        lHost.append("]");
        lTag.append(lHost);
        lTag.append("},");
        //closing attributes

        //measurements
        lTag.append("\"measurements\": {").append("\"condition\":").append(tag.measurements().condition()).append(",");
        lTag.append("\"values\": [");

        QByteArray lValues;
        for (double value : tag.measurements().values()) {
            lValues.append(QString::number(value));
            lValues.append(",");
        }
        lValues.remove(lValues.size()-1, 1);
        lTag.append(lValues);
        lTag.append("]},");
        //closing measurements

        //qualities
        lTag.append("\"qualities\" : {");
        lValues.clear();
        lValues.append("\"values\" : [");
        for (double value : tag.qualities()) {
            lValues.append(QString::number(value));
            lValues.append(",");
        }
        lValues.remove(lValues.size()-1, 1);
        lTag.append(lValues);
        lTag.append("]}");
        //closing qualities

        lTag.append("}");
        //closing filters

        lTag.append("}");

        rTags.append(lTag);
    }

    rTags.append("]}");
    return rTags;
}

QByteArray QTimeSeriesParser::formLatestDatapointsJson(QStringList tags)
{
    QByteArray rTags;
    rTags.append("{tags:[");

    QByteArray lTmpTag;
    for (QString tag : tags) {
        lTmpTag.append("{name: ").append(tag);
        lTmpTag.append("},");
    }
    lTmpTag.remove(lTmpTag.size()-1, 1);//remove last ,

    rTags.append(lTmpTag);
    rTags.append("]}");
    return rTags;
}

QByteArray QTimeSeriesParser::formLimitedDatapointsJson(QStringList tags, int count)
{
    QByteArray rTags;
    rTags.append("{start: 1y-ago, tags:[");

    QByteArray lTmpTag;
    for (QString tag : tags) {
        lTmpTag.append("{name: ").append(tag);
        lTmpTag.append(",order: desc,");
        lTmpTag.append("limit: ").append(QString::number(count));
        lTmpTag.append("},");
    }
    lTmpTag.remove(lTmpTag.size()-1, 1);//remove last ,

    rTags.append(lTmpTag);
    rTags.append("]}");
    return rTags;
}

QByteArray QTimeSeriesParser::formFromToDatapointsJson(QStringList tags, QString from, QString to)
{
    QByteArray rTags;
    rTags.append("{cache_time: 0, tags:[");

    QByteArray lTmpTag;
    for (QString tag : tags) {
        lTmpTag.append("{name: ").append(tag);
        lTmpTag.append(",order: desc");
        lTmpTag.append("},");
    }
    lTmpTag.remove(lTmpTag.size()-1, 1);//remove last ,

    rTags.append(lTmpTag);
    rTags.append("], start :").append(from).append(",");
    rTags.append("end : ").append(to);
    rTags.append("}");
    return rTags;
}

QByteArray QTimeSeriesParser::formDatapointsJson(QString name, double data, double quality, QJsonObject attributes)
{
    qint64 lTimeStamp = QDateTime::currentMSecsSinceEpoch();
    QJsonObject lObject;

    QJsonArray lBodyArray;
    QJsonObject lBody;
    QJsonArray lDataPointsArray;
    QJsonArray lData;


    lObject[TS_KEY_MESSAGE_ID] = lTimeStamp;

    lBody[TS_KEY_NAME] = name;

    lData.append(lTimeStamp);
    lData.append(data);
    lData.append(quality);
    lDataPointsArray.append(lData);
    lBody[TS_KEY_DATAPOINTS] = lDataPointsArray;

    if (!attributes.isEmpty()) {
        lBody[TS_KEY_ATTRIBUTES] = attributes;
    }

    lBodyArray.append(lBody);
    lObject[TS_KEY_BODY] = lBodyArray;

    return QJsonDocument(lObject).toJson();
}

QByteArray QTimeSeriesParser::margeJsons(QString parent, QString child)
{
    QByteArray rJson;

    if (!parent.isEmpty() && !child.isEmpty()) {
        QJsonDocument lParentJsonDoc = QJsonDocument::fromJson(parent.toUtf8());
        QJsonDocument lChildJsonDoc = QJsonDocument::fromJson(child.toUtf8());
        if (lParentJsonDoc.isObject() && lChildJsonDoc.isObject()) {

            QJsonObject lMargetObject = margeJsons(lParentJsonDoc.object(), lChildJsonDoc.object());
            QJsonDocument lDocument;
            lDocument.setObject(lMargetObject);

            rJson = lDocument.toJson();

        } else {
            qDebug() << "provided string for json marge are not json objects";
        }
    } else {
        qDebug() << "provided string for json marge are not json objects";
    }

    return rJson;
}

QJsonObject QTimeSeriesParser::margeJsons(QJsonObject parent, QJsonObject child)
{
    QJsonObject rObject;
    QString lMessageId = QString::number(QDateTime::currentMSecsSinceEpoch());
    rObject[TS_KEY_MESSAGE_ID] = lMessageId;

    QJsonArray lBodyArray;

    bool lParentValid = QTimeSeriesParser::isJsonValid(parent);
    bool lChildValid = QTimeSeriesParser::isJsonValid(child);

    if (lParentValid && lChildValid) {
        lBodyArray = margeBodyJsons(parent[TS_KEY_BODY].toArray(), child[TS_KEY_BODY].toArray());
    } else {
        qDebug() << "Received parent and child strings are not of json format";
    }

    rObject[TS_KEY_BODY] = lBodyArray;

    return rObject;
}

QJsonArray QTimeSeriesParser::margeBodyJsons(QJsonArray parent, QJsonArray child)
{
    QJsonArray rBodyArray;

    for (QJsonValue parentBodyJson : parent) {
        for (QJsonValue childBodyJson : child) {
            QString lParentName = parentBodyJson.toObject()[TS_KEY_NAME].toString();
            QString lChildName = childBodyJson.toObject()[TS_KEY_NAME].toString();

            QJsonArray lParentDP = parentBodyJson.toObject()[TS_KEY_DATAPOINTS].toArray();
            QJsonArray lChildDP = childBodyJson.toObject()[TS_KEY_DATAPOINTS].toArray();

            QJsonObject lParentAtt = parentBodyJson.toObject()[TS_KEY_ATTRIBUTES].toObject();
            QJsonObject lChildAtt = childBodyJson.toObject()[TS_KEY_ATTRIBUTES].toObject();

            if (lParentName == lChildName) {//merge body if child and parent have the same name
                QJsonObject lBodyObject;

                //adding name to body object
                lBodyObject[TS_KEY_NAME] = lParentName;

                if (areAttibuteKeysEqual(lParentAtt, lChildAtt)) {
                    //adding marged datapoints with only unique timestamps to body object
                    QJsonArray lDPArray = lParentDP;
                    QJsonArray lChildArray;
                    for (QJsonValue childValue : lChildDP) {
                        lChildArray = childValue.toArray();

                        lDPArray.append(lChildArray);
                    }

                    lBodyObject[TS_KEY_DATAPOINTS] = lDPArray;

                    //adding marged attributes to body object
                    lBodyObject[TS_KEY_ATTRIBUTES] = lParentAtt;

                    //adding body object to body array
                    rBodyArray.append(lBodyObject);
                } else {
                    rBodyArray.append(parentBodyJson.toObject());
                    rBodyArray.append(childBodyJson.toObject());
                }
            } else {// just add one after other if bodies have different names
                rBodyArray.append(parentBodyJson.toObject());
                rBodyArray.append(childBodyJson.toObject());
            }
        }
    }

    return rBodyArray;
}

bool QTimeSeriesParser::areAttibuteKeysEqual(QJsonObject parent, QJsonObject child)
{
    bool rEqual = true;

    QStringList lParentKeys = parent.keys();
    QStringList lChildKeys = child.keys();


    QSet<QString> lParentSet = lParentKeys.toSet();
    QSet<QString> lChildSet = lChildKeys.toSet();

    QSet<QString> lResult = lParentSet.subtract(lChildSet);

    if ((lParentKeys.count() == lChildKeys.count()) && lResult.count() == 0) {
        for (QString key : lChildKeys) {
            if (parent[key] != child[key]) {
                rEqual = false;
            }
        }
    } else {
        rEqual = false;
    }

    return rEqual;
}

QStringList QTimeSeriesParser::parseTagsResponse(QByteArray jsonData)
{
    QStringList rTags;

    QJsonDocument lJsonDoc = QJsonDocument::fromJson(jsonData);
    if (lJsonDoc.isObject()) {
        QJsonObject lJson(lJsonDoc.object());

        for (QJsonValue value : lJson[TS_KEY_RESULTS].toArray()) {
            rTags.append(value.toString());
        }

    } else {
        qDebug() << "Data received is not JSON Object";
    }

    return rTags;
}

bool QTimeSeriesParser::isJsonValid(QJsonObject json)
{
    bool rValid = true;

    if (!json[TS_KEY_MESSAGE_ID].isString()) {
        rValid = false;
    }

    if (!json[TS_KEY_BODY].isArray()) {
        rValid = false;
    } else {
        QJsonArray lBody = json[TS_KEY_BODY].toArray();
        if (lBody.count() > 0) {
            QJsonObject lBodyObject = lBody.at(0).toObject();
            if (!lBodyObject[TS_KEY_NAME].isString()) {
                rValid = false;
            }

            if (!lBodyObject[TS_KEY_DATAPOINTS].isArray()) {
                rValid = false;
            }

            if (!lBodyObject[TS_KEY_ATTRIBUTES].isObject()) {
                rValid = false;
            }
        }
    }

    return  rValid;
}
