#include "qtimeseriestag.h"

QTimeSeriesTag::QTimeSeriesTag()
{

}

QString QTimeSeriesTag::name() const
{
    return mName;
}

void QTimeSeriesTag::setName(const QString &name)
{
    mName = name;
}

bool QTimeSeriesTag::suppressGroupByType() const
{
    return mSuppressGroupByType;
}

void QTimeSeriesTag::setSuppressGroupByType(bool suppressGroupByType)
{
    mSuppressGroupByType = suppressGroupByType;
}

QStringList QTimeSeriesTag::attributes() const
{
    return mAttributes;
}

void QTimeSeriesTag::setAttributes(const QStringList &attributes)
{
    mAttributes = attributes;
}

QList<double> QTimeSeriesTag::qualities() const
{
    return mQualities;
}

void QTimeSeriesTag::setQualities(const QList<double> &qualities)
{
    mQualities = qualities;
}

QTimeSeriesMeasurements QTimeSeriesTag::measurements() const
{
    return mMeasurements;
}

void QTimeSeriesTag::setMeasurements(QTimeSeriesMeasurements measurements)
{
    mMeasurements = measurements;
}

QString QTimeSeriesMeasurements::condition() const
{
    return mCondition;
}

void QTimeSeriesMeasurements::setCondition(const QString &value)
{
    mCondition = value;
}

QList<double> QTimeSeriesMeasurements::values() const
{
    return mValues;
}

void QTimeSeriesMeasurements::setValues(const QList<double> &value)
{
    mValues = value;
}
