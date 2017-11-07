/***************************************************************************
 *                                                                         *
 *   This Predix services API was created by by Indeema Software Inc.      *
 *   QPredix SDK is under MIT license so you are free to use it.           *
 *   https://indeema.com                                                   *
 *                                                                         *
 *   In case if you have any issues or comments, please conntact us:       *
 *   support@indeema.com                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QTIMESERIESPARSER_H
#define QTIMESERIESPARSER_H

#include "qtimeseriestag.h"

#include <QList>
#include <QStringList>
#include <QJsonObject>

class QTimeSeriesParser
{
public:
    QTimeSeriesParser();

    static QByteArray formRequestJson(QList<QTimeSeriesTag>);
    static QByteArray formLatestDatapointsJson(QStringList);
    static QByteArray formLimitedDatapointsJson(QStringList, int count);
    static QByteArray formFromToDatapointsJson(QStringList, QString from, QString to);

//    static QByteArray formDatapointsJson(QString name, QString data, QString quality, QString attributes=nullptr);
    static QByteArray formDatapointsJson(QString name, QString data, QString quality, QJsonObject attributes=QJsonObject());

    static QByteArray margeJsons(QString parent, QString child);
    static QJsonObject margeJsons(QJsonObject parent, QJsonObject child);
    static QJsonArray margeBodyJsons(QJsonArray parent, QJsonArray child);
    static bool areAttibuteKeysEqual(QJsonObject parent, QJsonObject child);

    static QStringList parseTagsResponse(QByteArray);

    static bool isJsonValid(QJsonObject json);
};

#endif // QTIMESERIESPARSER_H
