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
#include "qtimeseriesdatapoint.h"

#include <QList>
#include <QStringList>

class QTimeSeriesParser
{
public:
    QTimeSeriesParser();

    static QByteArray formRequestJson(QList<QTimeSeriesTag>);
    static QByteArray formLatestDatapointsJson(QStringList);
    static QByteArray formLimitedDatapointsJson(QStringList, int count);
    static QByteArray formFromToDatapointsJson(QStringList, QString from, QString to);

    static QByteArray formDatapointsJson(QString name, QList<QTimeSeriesDataPoint> datapoints);

    static QByteArray formDatapointsJson(QString name, QString data, QString quality, QString attributes=nullptr);

    static QStringList parseTagsResponse(QByteArray);
};

#endif // QTIMESERIESPARSER_H
