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

#ifndef QTIMESERIESDATAPOINT_H
#define QTIMESERIESDATAPOINT_H

#include <QString>

class QTimeSeriesDataPoint
{
public:
    QTimeSeriesDataPoint();

    QString timeStamp() const;
    void setTimeStamp(const QString &timeStamp);

    QString data() const;
    void setData(const QString &data);

private:
    QString mTimeStamp;
    QString mData;
};

#endif // QTIMESERIESDATAPOINT_H
