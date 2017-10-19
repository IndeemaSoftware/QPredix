#include "qtimeseriesrequests.h"
#include "qtimeseriesparser.h"
#include "qtimeseriescommands.h"
#include "../QUaa/quaa.h"

#include <QNetworkReply>
#include <QDebug>
#include <QWebSocket>

QTimeSeriesRequests::QTimeSeriesRequests(QUaa *uaa, QPredixCore *parent) : QPredixCore(uaa->uaaInfo().uaaUrl(), uaa->uaaInfo().base64ClientCredential(), parent),
    mUaa{uaa},
    mRequestType{QTimeSeriesRequestsTypeNone}
{
    setUrl(QTS_URL);

    mWebSocket = new QWebSocket();
    connect(mWebSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(mWebSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mWebSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(mWebSocket, SIGNAL(pong(quint64, const QByteArray &)), this, SLOT(pong(quint64, const QByteArray &)));
    connect(mWebSocket, SIGNAL(textMessageReceived(const QString &)), this, SLOT(textMessageReceived(const QString &)));
}

QTimeSeriesRequests::~QTimeSeriesRequests()
{
    mWebSocket->close();
    delete mWebSocket;
}

void QTimeSeriesRequests::getAllTags(QString zoneId)
{
    QUrl lServiceURL(formUrl(QTS_CMD_TAGS, APIVersion()));

    QNetworkRequest lRequest(request(lServiceURL, zoneId));

    mgr()->get(lRequest);
}

void QTimeSeriesRequests::getLatestDatapoints(QStringList tags, QString zoneId)
{
    mRequestType = QTimeSeriesRequestsTypeTags;
    QUrl lServiceURL(formUrl(QTS_CMD_LATEST, APIVersion()));

    QByteArray lDataString = QTimeSeriesParser::formLatestDatapointsJson(tags);

    QNetworkRequest lRequest(request(lServiceURL, zoneId));

    mgr()->post(lRequest, lDataString);
}

void QTimeSeriesRequests::sendCustomRequest(QString dataString, QString zoneId)
{
    mRequestType = QTimeSeriesRequestsTypeCustom;

    QUrl lServiceURL(formUrl(QTS_CMD_DATAPOINTS, APIVersion()));

    QNetworkRequest lRequest(request(lServiceURL, zoneId));

    mgr()->post(lRequest, dataString.toUtf8());
}

void QTimeSeriesRequests::getLimitedDatapoints(QStringList tags, int count, QString zoneId)
{
    mRequestType = QTimeSeriesRequestsTypeLimited;

    QUrl lServiceURL(formUrl(QTS_CMD_DATAPOINTS, APIVersion()));

    QByteArray lDataString = QTimeSeriesParser::formLimitedDatapointsJson(tags, count);

    QNetworkRequest lRequest(request(lServiceURL, zoneId));

    mgr()->post(lRequest, lDataString);
}

void QTimeSeriesRequests::getFromToDatapoints(QStringList tags, QString from, QString to, QString zoneId)
{
    mRequestType = QTimeSeriesRequestsTypeFromTo;

    QUrl lServiceURL(formUrl(QTS_CMD_DATAPOINTS, APIVersion()));

    QByteArray lDataString = QTimeSeriesParser::formFromToDatapointsJson(tags, from, to);

    QNetworkRequest lRequest(request(lServiceURL, zoneId));

    mgr()->post(lRequest, lDataString);
}

void QTimeSeriesRequests::authenticationRequired(QNetworkReply *, QAuthenticator *a)
{
    qDebug() << a;
}

void QTimeSeriesRequests::sslErrors(QNetworkReply *, const QList<QSslError> &l)
{
    qDebug() << l;
}

void QTimeSeriesRequests::handleResponse(QNetworkReply *reply)
{
    QByteArray lResponse = reply->readAll();
    qDebug() << "QTimeSeriesRequests response: " << lResponse;

    if (reply->error() == QNetworkReply::NoError) {
        if (QString(QTS_CMD_TAGS).contains(getCommand(reply))) {
            emit tagsReceived(lResponse);
        } else if (QString(QTS_CMD_DATAPOINTS).contains(getCommand(reply))) {
            switch(mRequestType) {
            case QTimeSeriesRequestsTypeCustom:{
                emit customRequestResponseReceived(lResponse);
            }
                break;
            case QTimeSeriesRequestsTypeLimited:{
                emit limitedDatapointsReceived(lResponse);
            }
                break;
            case QTimeSeriesRequestsTypeFromTo:{
                emit fromToDatapointsReceived(lResponse);
            }
                break;
            }
        } else if (QString(QTS_CMD_LATEST).contains(getCommand(reply))) {
            emit latestDatapointsReceived(lResponse);
        }
    } else {
        qDebug() << reply->error();
    }

    mRequestType = QTimeSeriesRequestsTypeNone;
}

void QTimeSeriesRequests::setUaa(QUaa *uaa)
{
    mUaa = uaa;
}

void QTimeSeriesRequests::sendData(QString name, QString data, QString quality,QString attributes)
{
    QByteArray lData = QTimeSeriesParser::formDatapointsJson(name, data, quality, attributes);

    qDebug() << lData;

    mDataToSend = QString().fromUtf8(lData);
}

#define QSSLSOCKET_DEBUG

void QTimeSeriesRequests::openSocket(QString zoneId)
{
    QNetworkRequest lRequest(QUrl(TS_WEBSOCKET_URL));
    lRequest.setRawHeader("Predix-Zone-Id", zoneId.toUtf8());
    lRequest.setRawHeader("Origin", TS_WEBSOCKET_ORIGIN.toUtf8());
    lRequest.setRawHeader("Authorization", mUaa->clientSessionInfo().token().toUtf8());

    mWebSocket->open(lRequest);
}

void QTimeSeriesRequests::closeSocket()
{
    mWebSocket->close();
}

QNetworkRequest QTimeSeriesRequests::request(QUrl url, QString zoneId)
{
    QNetworkRequest rRequest(url);
    rRequest.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    rRequest.setRawHeader("Predix-Zone-Id", zoneId.toUtf8());
    rRequest.setRawHeader("Authorization", mUaa->clientSessionInfo().token().toUtf8());

    return rRequest;
}

void QTimeSeriesRequests::connected()
{
    qDebug() << __FUNCTION__;
    mWebSocket->sendTextMessage(mDataToSend);
}

void QTimeSeriesRequests::disconnected()
{
    qDebug() << __FUNCTION__;
}

void QTimeSeriesRequests::pong(quint64 elapsedTime, const QByteArray &payload)
{
    qDebug() << __FUNCTION__;
    qDebug() << payload;
}

void QTimeSeriesRequests::textMessageReceived(const QString &message)
{
    qDebug() << __FUNCTION__;
    qDebug() << message;
}

void QTimeSeriesRequests::error(QAbstractSocket::SocketError error)
{
    qDebug() << __FUNCTION__;
    qDebug() << error << mWebSocket->errorString();
}
