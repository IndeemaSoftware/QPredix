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
