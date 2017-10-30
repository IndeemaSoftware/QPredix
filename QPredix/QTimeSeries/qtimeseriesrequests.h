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

#ifndef QTIMESERIESREQUESTS_H
#define QTIMESERIESREQUESTS_H

#include "../QPredixCore/qpredixcore.h"
#include "qtimeseriestag.h"

#include <QAbstractSocket>
#include <QJsonObject>

class QUaa;
class QWebSocket;
class QFile;

typedef enum {
    QTimeSeriesRequestsTypeNone = -1,
    QTimeSeriesRequestsTypeTags,
    QTimeSeriesRequestsTypeLatest,
    QTimeSeriesRequestsTypeCustom,
    QTimeSeriesRequestsTypeLimited,
    QTimeSeriesRequestsTypeFromTo
} QTimeSeriesRequestsType;

class QTimeSeriesRequests : public QPredixCore
{
    Q_OBJECT
public:
    QTimeSeriesRequests(QUaa*, QPredixCore *parent = 0);
    ~QTimeSeriesRequests();

    void loadLatestMeasurements(QList<QTimeSeriesTag>);

    void getAllTags(QString zoneId);
    void getLatestDatapoints(QStringList tags, QString zoneId);
    void sendCustomRequest(QString dataString, QString zoneId);
    void getLimitedDatapoints(QStringList tags, int count, QString zoneId);
    void getFromToDatapoints(QStringList tags, QString from, QString to, QString zoneId);

    void setUaa(QUaa *uaa);

    //! You can use sendData method to send data to Predix.
    /*!
        \param body JSON body ofhttps://time-series-store-predix.run.aws-usw02-pr.ice.predix.io/datapoints query
    */
    void sendData(QString name, QString data, QString quality, QString attributes=nullptr);
    void sendData(QJsonObject object);

    void openSocket(QString zoneId);
    void closeSocket();

protected:
    QNetworkRequest request(QUrl url, QString zoneId);

private:
    void sendDataToSocket();
    void accumulateDataToSend(QString data);
    void readStoredData();
    void saveAccumulatedData();

signals:
    void tagsReceived(QByteArray);
    void latestDatapointsReceived(QByteArray);
    void customRequestResponseReceived(QByteArray);
    void limitedDatapointsReceived(QByteArray);
    void fromToDatapointsReceived(QByteArray);

protected slots:
    void connected();
    void disconnected();
    void textMessageReceived(const QString &message);
    void error(QAbstractSocket::SocketError error);
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void handleResponse(QNetworkReply *reply);

private:
    QUaa *mUaa;
    QTimeSeriesRequestsType mRequestType;
    QWebSocket *mWebSocket;

    QString mDataToSend;
    QFile *mDataFile;
};

#endif // QTIMESERIESREQUESTS_H
