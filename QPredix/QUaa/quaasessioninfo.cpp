#include "quaasessioninfo.h"

#include "../QPredixCore/qpredixcore.h"

QUaaSessionInfo::QUaaSessionInfo()
{

}

QString QUaaSessionInfo::token() const
{
    return mToken;
}

void QUaaSessionInfo::setToken(const QString &token)
{
    mToken = token;
}

QString QUaaSessionInfo::tokenType() const
{
    return mTokenType;
}

void QUaaSessionInfo::setTokenType(const QString &tokenType)
{
    mTokenType = tokenType;
}

QString QUaaSessionInfo::refreshToken() const
{
    return mRefreshToken;
}

void QUaaSessionInfo::setRefreshToken(const QString &refreshToken)
{
    mRefreshToken = refreshToken;
}

int QUaaSessionInfo::expiresIn() const
{
    return mExpiresIn;
}

void QUaaSessionInfo::setExpiresIn(const int expiresIn)
{
    mExpiresIn = expiresIn;
}

QStringList QUaaSessionInfo::scope() const
{
    return mScope;
}

void QUaaSessionInfo::setScope(const QStringList &scope)
{
    mScope = scope;
}

QString QUaaSessionInfo::jti() const
{
    return mJti;
}

void QUaaSessionInfo::setJti(const QString &jti)
{
    mJti = jti;
}
