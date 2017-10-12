#ifndef QUAASESSIONINFO_H
#define QUAASESSIONINFO_H

#include <QString>
#include <QStringList>

class QUaaSessionInfo
{
public:
    QUaaSessionInfo();

    QString token() const;
    void setToken(const QString &token);

    QString tokenType() const;
    void setTokenType(const QString &tokenType);

    QString refreshToken() const;
    void setRefreshToken(const QString &refreshToken);

    int expiresIn() const;
    void setExpiresIn(const int expiresIn);

    QStringList scope() const;
    void setScope(const QStringList &scope);

    QString jti() const;
    void setJti(const QString &jti);

private:
    QString mToken;
    QString mTokenType;
    QString mRefreshToken;
    int mExpiresIn;
    QStringList mScope;
    QString mJti;
};

#endif // QUAASESSIONINFO_H
