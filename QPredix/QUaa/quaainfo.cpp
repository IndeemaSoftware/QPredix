#include "quaainfo.h"

#include "../QPredixCore/qpredixcore.h"

#include <QDebug>

QUaaInfo::QUaaInfo() :
    mUaaUrl{UNDEFINED},
    mBase64ClientCredential{UNDEFINED}
{
}

QUaaInfo::QUaaInfo(QUaaInfo *info)
{
    this->setUaaUrl(info->uaaUrl());
    this->setBase64ClientCredential(info->base64ClientCredential());
}

bool QUaaInfo::isValid()
{
    bool rIsValid = true;

    checkCredentials();

    if (mBase64ClientCredential.isEmpty()) {
        rIsValid = false;
    }

    if (mUaaUrl.isEmpty()) {
        rIsValid = false;
    }

    return rIsValid;
}

QString QUaaInfo::uaaUrl() const
{
    return mUaaUrl;
}

void QUaaInfo::setUaaUrl(const QString &uaaUrl)
{
    mUaaUrl = uaaUrl;
}

QString QUaaInfo::base64ClientCredential() const
{
    return mBase64ClientCredential;
}

void QUaaInfo::setBase64ClientCredential(const QString &base64ClientCredential)
{
    mBase64ClientCredential = base64ClientCredential;
}

void QUaaInfo::setClientCredential(const QString &login, const QString secret)
{
    QString lData;
    lData.append(login);
    lData.append(":");
    lData.append(secret);

    setBase64ClientCredential(lData.toUtf8().toBase64());
}

void QUaaInfo::checkCredentials()
{
    if (mBase64ClientCredential == UNDEFINED) {
        qDebug() << "Please set client credentials in format - base64 \"client_id:secret\"";
    }

    if (mUaaUrl == UNDEFINED) {
        qDebug() << "Predix Uaa url is missing";
    }

}
