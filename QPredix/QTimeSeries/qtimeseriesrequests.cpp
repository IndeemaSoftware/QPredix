#include "qtimeseriesrequests.h"
#include "qtimeseriesparser.h"
#include "qtimeseriescommands.h"
#include "../QUaa/quaa.h"

#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QWebSocket>
#include <QFile>

QTimeSeriesRequests::QTimeSeriesRequests(QUaa *uaa, QPredixCore *parent) : QPredixCore(uaa->uaaInfo().uaaUrl(), uaa->uaaInfo().base64ClientCredential(), parent),
    mUaa{uaa},
    mRequestType{QTimeSeriesRequestsTypeNone},
    mDataToSend{""},
    mDataFile{new QFile(TS_DATA_FILE)}
{
    setUrl(QTS_URL);

    mWebSocket = new QWebSocket();
    connect(mWebSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(mWebSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mWebSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(mWebSocket, SIGNAL(textMessageReceived(const QString &)), this, SLOT(textMessageReceived(const QString &)));

    readStoredData();
}

QTimeSeriesRequests::~QTimeSeriesRequests()
{
    saveAccumulatedData();

    mWebSocket->close();
    delete mWebSocket;

    delete mDataFile;
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

    accumulateDataToSend(QString().fromUtf8(lData));

//    sendDataToSocket();
}

void QTimeSeriesRequests::sendData(QJsonObject object)
{
    QJsonDocument lDocument;
    lDocument.setObject(object);

    accumulateDataToSend(lDocument.toJson());

//    sendDataToSocket();
}

#define QSSLSOCKET_DEBUG

void QTimeSeriesRequests::openSocket(QString zoneId)
{
    if (!mUaa->clientSessionInfo().token().isEmpty()) {
        QNetworkRequest lRequest(QUrl(TS_WEBSOCKET_URL));
        lRequest.setRawHeader("Predix-Zone-Id", zoneId.toUtf8());
        lRequest.setRawHeader("Origin", TS_WEBSOCKET_ORIGIN.toUtf8());
        lRequest.setRawHeader("Authorization", mUaa->clientSessionInfo().token().toUtf8());

        mWebSocket->open(lRequest);
    } else {
        qDebug() << "Client was not authenticated. All data is stored locally.";
    }
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

void QTimeSeriesRequests::sendDataToSocket()
{
    qDebug() << "data to be sent: " << mDataToSend;
    if (mWebSocket->isValid() && !mDataToSend.isEmpty()) {
        mWebSocket->sendTextMessage(mDataToSend);
    } else if (!mDataToSend.isEmpty()) {
        qDebug() << "saving data is socket is closed";
        saveAccumulatedData();
    }

    mDataToSend = "";
}

void QTimeSeriesRequests::accumulateDataToSend(QString data)
{
    if (!mDataToSend.isEmpty()) {
        mDataToSend = QTimeSeriesParser::margeJsons(mDataToSend, data);
    } else {
        mDataToSend = data;
        qDebug() << "There no data to send!";
    }
}

void QTimeSeriesRequests::readStoredData()
{
    if (mDataFile->isOpen()) {
        mDataFile->close();
        while (mDataFile->isOpen()) {}
    }

    if (mDataFile->open(QIODevice::ReadWrite)) {
        QString lDataInFile = QString().fromUtf8(mDataFile->readAll());
        if (!lDataInFile.isEmpty()) {
            mDataToSend = QTimeSeriesParser::margeJsons(lDataInFile, mDataToSend);

            mDataFile->write("", 0);
            mDataFile->close();
            qDebug() << "data read from file: " << mDataToSend;
        } else {
            qDebug() << "datastore is empty";
        }
    } else {
        qDebug() << "Something went wrong while trying to open " << TS_DATA_FILE;
    }
}

void QTimeSeriesRequests::saveAccumulatedData()
{
    if (mDataFile->isOpen()) {
        mDataFile->close();
        while (mDataFile->isOpen()) {}
    }

    if (!mDataToSend.isEmpty()) {
        if (mDataFile->open(QIODevice::WriteOnly)) {
            QTextStream lStream(mDataFile);
            lStream << mDataToSend;
            qDebug() << "Data saved locally: " << mDataToSend;

            mDataToSend = "";

            mDataFile->close();
        } else {
            qDebug() << "Something went wrong while trying to open." << TS_DATA_FILE;
        }
    }
}

void QTimeSeriesRequests::connected()
{
    readStoredData();
    sendDataToSocket();
}

void QTimeSeriesRequests::disconnected()
{
    qDebug() << __FUNCTION__;
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
