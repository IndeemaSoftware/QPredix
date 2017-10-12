#ifndef QTIMESERIES_H
#define QTIMESERIES_H

#include "qtimeseries_global.h"

#include <QObject>
#include <QStringList>

class QUaa;
class QTimeSeriesRequests;

class QTIMESERIESSHARED_EXPORT QTimeSeries : public QObject
{
    Q_OBJECT

public:
    explicit QTimeSeries(QUaa*, QObject *parent=0);
    ~QTimeSeries();

    void sendCustomRequest(QString);
    void getTags();
    void getLatestDatapoints(QStringList);
    void getLimitedDatapoints(QStringList tags, int count);
    void getFromToDatapoints(QStringList tags, QString from, QString to);

    void sendData(QString tagName, QString data);
    void openSocket();

    QString zoneID() const;
    void setZoneID(const QString &zoneID);

signals:
    void tagsList(QStringList);
    void latestDatapoints(QByteArray);
    void customRequestResponse(QByteArray);
    void limitedDatapoints(QByteArray);
    void fromToDatapoints(QByteArray);

private slots:
    void tagsReceived(QByteArray);

private:
    QUaa *mUaa;
    QString mZoneID;
    QTimeSeriesRequests *mRequest;
};

#endif // QTIMESERIES_H
