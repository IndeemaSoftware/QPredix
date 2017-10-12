#include "qtimeseriesdatapoint.h"

QTimeSeriesDataPoint::QTimeSeriesDataPoint()
{

}

QString QTimeSeriesDataPoint::timeStamp() const
{
    return mTimeStamp;
}

void QTimeSeriesDataPoint::setTimeStamp(const QString &timeStamp)
{
    mTimeStamp = timeStamp;
}

QString QTimeSeriesDataPoint::data() const
{
    return mData;
}

void QTimeSeriesDataPoint::setData(const QString &data)
{
    mData = data;
}
