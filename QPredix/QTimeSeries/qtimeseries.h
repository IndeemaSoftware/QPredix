#ifndef QTIMESERIES_H
#define QTIMESERIES_H
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

#include <QObject>
#include <QStringList>

class QUaa;
class QTimeSeriesRequests;

class QTimeSeries : public QObject
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

    void sendData(QString tagName, QString data, QString quality="3", QString attributes=nullptr);
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
