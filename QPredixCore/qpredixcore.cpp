#include "qpredixcore.h"

#include <QNetworkReply>

QPredixCore::QPredixCore(QString url, QString cred, QObject *parent) : QObject(parent),
    mAPIVersion{DEFAULT_API_VERSION}
{
    setUrl(url);
    setClientCredentials(cred);

    mMgr = new QNetworkAccessManager();
    connect(mMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResponse(QNetworkReply*)));
    connect(mMgr, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)), this, SLOT(sslErrors(QNetworkReply *, const QList<QSslError> &)));
    connect(mMgr, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));
}

QPredixCore::~QPredixCore()
{
    delete mMgr;
}

QString QPredixCore::clientCredentials() const
{
    return mClientCredentials;
}

void QPredixCore::setClientCredentials(const QString &clientCredentials)
{
    mClientCredentials = clientCredentials;
}

QString QPredixCore::url() const
{
    return mUrl;
}

void QPredixCore::setUrl(const QString &url)
{
    mUrl = url;
}

QString QPredixCore::clientId()
{
    QString rClientId = UNDEFINED;

    QString lCredentials = QString().fromUtf8(QByteArray().fromBase64(clientCredentials().toUtf8()));
    QStringList lCredList = lCredentials.split(":");

    if (lCredList.count() > 0) {
        rClientId = lCredList.at(0);
    }

    return rClientId;
}

QString QPredixCore::secret()
{
    QString rSecret = UNDEFINED;

    QString lCredentials = QString().fromUtf8(QByteArray().fromBase64(clientCredentials().toUtf8()));
    QStringList lCredList = lCredentials.split(":");

    if (lCredList.count() > 0) {
        rSecret = lCredList.at(1);
    }

    return rSecret;

}

QNetworkAccessManager *QPredixCore::mgr() const
{
    return mMgr;
}

QString QPredixCore::getVersion(QNetworkReply *reply)
{
    QString rVersion(UNDEFINED);

    if (!reply->request().url().path().isEmpty()) {
        rVersion = reply->request().url().path();
    }

    if (UNDEFINED != rVersion) {
        rVersion = rVersion.mid(0, rVersion.indexOf("/", 1));
        rVersion.remove(0, 1);
    }

    return rVersion;
}

QString QPredixCore::getCommand(QNetworkReply *reply)
{
    QString rCommand(UNDEFINED);
    QString lVersion = getVersion(reply);

    if (!reply->request().url().path().isEmpty()) {
        rCommand = reply->request().url().path();
    }

    if (UNDEFINED != rCommand) {
        QString lTmp("/");
        lTmp.append(lVersion);
        lTmp.append("/");

        rCommand.remove(lTmp);// removing version from path
        rCommand.remove(rCommand.size()-1, 1);//removing last / from path
    }

    return rCommand;
}

QNetworkRequest QPredixCore::request(QUrl url)
{
    QNetworkRequest lRequest(url);
    lRequest.setRawHeader("Pragma", "no-cache");
    lRequest.setRawHeader("content-type", "application/x-www-form-urlencoded");
    lRequest.setRawHeader("Cache-Control", "no-cache");
    lRequest.setRawHeader("authorization", QByteArray("Basic ").append(clientCredentials()));

    return lRequest;
}

QByteArray QPredixCore::serverUrl(QByteArray version)
{
    QByteArray rServerUrl = url().toUtf8();
    rServerUrl.append(version);

    return rServerUrl;
}

QString QPredixCore::APIVersion() const
{
    return mAPIVersion;
}

void QPredixCore::setAPIVersion(const QString &aPIVersion)
{
    mAPIVersion = aPIVersion;
}

QString QPredixCore::formUrl(QString url)
{
    return QString(mUrl.toUtf8().append(url));

}

QString QPredixCore::formUrl(QString url, QString version)
{
    return QString(mUrl.toUtf8().append("/").append(version).append(url));

}
