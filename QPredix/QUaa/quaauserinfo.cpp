#include "quaauserinfo.h"

QUaaUserInfo::QUaaUserInfo()
{

}

QString QUaaUserInfo::code() const
{
    return mCode;
}

void QUaaUserInfo::setCode(const QString &code)
{
    mCode = code;
}

QString QUaaUserInfo::login() const
{
    return mLogin;
}

void QUaaUserInfo::setLogin(const QString &login)
{
    mLogin = login;
}

QString QUaaUserInfo::password() const
{
    return mPassword;
}

void QUaaUserInfo::setPassword(const QString &password)
{
    mPassword = password;
}
