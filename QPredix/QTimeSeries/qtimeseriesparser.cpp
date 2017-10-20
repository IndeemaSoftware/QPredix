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


QByteArray QTimeSeriesParser::formDatapointsJson(QString name, QString data, QString quality, QString attributes)
{
//    if (timeStamp.isEmpty()) {
    QString lTimeStamp = QString::number(QDateTime::currentMSecsSinceEpoch());
//    }

    QByteArray rTags("{ \"messageId\" :\"");
    rTags.append(lTimeStamp).append("\",");
    rTags.append("\"body\" : [ {");

    rTags.append("\"name\" : \"").append(name).append("\",");
    rTags.append("\"datapoints\" : [[\"");

    rTags.append(lTimeStamp).append("\",\"");
    rTags.append(data).append("\", \"");
    rTags.append(quality);

    if (attributes == nullptr) {
        rTags.append("\"]]");
    } else {
        rTags.append("\"]],");
        rTags.append("\"attributes\" :").append(attributes);
    }

    rTags.append("}]}");
    return rTags;
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
