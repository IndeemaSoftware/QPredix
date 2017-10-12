#include "quaainfo.h"

QUaaInfo::QUaaInfo()
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
