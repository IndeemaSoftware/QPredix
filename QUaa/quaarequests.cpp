#include "quaarequests.h"
#include "quaacommands.h"
#include "quaaparser.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

QUaaRequests::QUaaRequests(QString url, QString cred, QPredixCore *parent) : QPredixCore(url, cred, parent)
{
}

void QUaaRequests::loginUser(QString userName, QString password)
{
    qDebug() << __FUNCTION__;
    QUrl lServiceURL(QString(url().toUtf8()).append(QUAA_CMD_AUTH));

    QByteArray lDataString = "username=";
    lDataString.append(userName.toUtf8());
    lDataString.append("&password=");
    lDataString.append(password.toUtf8());
    lDataString.append("&grant_type=");
    lDataString.append(GRANT_TYPE_PASS);

    mgr()->post(request(lServiceURL), lDataString);
}

void QUaaRequests::loginClient()
{
    qDebug() << __FUNCTION__;
    QUrl lServiceURL(QString(url().toUtf8()).append(QUAA_CMD_AUTH));

    QNetworkRequest lRequest(lServiceURL);
    lRequest.setRawHeader("Authorization ", QString("Basic ").append(clientCredentials()).toUtf8());
    lRequest.setRawHeader("Pragma", "no-cache");
    lRequest.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    qDebug() << clientCredentials().toUtf8();
    qDebug() << "Client ID: " << clientId();

    QByteArray lDataString = "client_id=";
    lDataString.append(clientId());
    lDataString.append("&grant_type=");
    lDataString.append(GRANT_TYPE_CREDNTIALS);

    mgr()->post(lRequest, lDataString);
}

void QUaaRequests::refreshToken(QString tokenRefresh)
{
    QUrl lServiceURL(QString(url().toUtf8()).append(QUAA_CMD_AUTH));

    QByteArray lDataString = "client_id=";
    lDataString.append(clientId().toUtf8());
    lDataString.append("&client_secret=");
    lDataString.append(secret().toUtf8());
    lDataString.append("&grant_type=");
    lDataString.append(GRANT_TYPE_REFRESH);
    lDataString.append("&token_format=");
    lDataString.append("opaque");
    lDataString.append("&refresh_token=");
    lDataString.append(tokenRefresh.toUtf8());

    mgr()->post(request(lServiceURL), lDataString);
}

void QUaaRequests::authenticationRequired(QNetworkReply*, QAuthenticator*)
{
    qDebug() << __FUNCTION__;
}

void QUaaRequests::sslErrors(QNetworkReply*reply, const QList<QSslError>&)
{
    qDebug() << __FUNCTION__;
    qDebug() << reply->readAll();
}

void QUaaRequests::handleResponse(QNetworkReply *reply)
{
    QByteArray lResponceData = reply->readAll();
    qDebug() << "Handle response: " << lResponceData;

    if (reply->error() == QNetworkReply::NoError) {
        if (QString(QUAA_CMD_AUTH).contains(getCommand(reply))) {
            QUaaSessionInfo lSessionInfo = QUaaParser::parseUaaLoginResponse(lResponceData);

            emit loginSucceed(lSessionInfo);
        }
    } else {
        if (QString(QUAA_CMD_AUTH).contains(getCommand(reply))) {
            emit loginFailed("Bad credentials");
        }

        qDebug() << "request failed: " << reply;
    }
}
