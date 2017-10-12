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

#ifndef QTIMESERIESTAG_H
#define QTIMESERIESTAG_H

#include <QString>
#include <QList>
#include <QStringList>

struct QTimeSeriesMeasurements
{
public:
    QString condition() const;
    void setCondition(const QString &value);

    QList<double> values() const;
    void setValues(const QList<double> &value);

private:
    QString mCondition;
    QList<double> mValues;
};

class QTimeSeriesTag
{
public:
    QTimeSeriesTag();

    QString name() const;
    void setName(const QString &name);

    bool suppressGroupByType() const;
    void setSuppressGroupByType(bool suppressGroupByType);

    QStringList attributes() const;
    void setAttributes(const QStringList &attributes);

    QList<double> qualities() const;
    void setQualities(const QList<double> &qualities);

    QTimeSeriesMeasurements measurements() const;
    void setMeasurements(const QTimeSeriesMeasurements measurements);

private:
    QString mName;
    bool mSuppressGroupByType;
    QStringList mAttributes;
    QList<double> mQualities;
    QTimeSeriesMeasurements mMeasurements;
};

#endif // QTIMESERIESTAG_H
