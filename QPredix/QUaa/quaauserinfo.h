#ifndef QUAAUSERINFO_H
#define QUAAUSERINFO_H

#include <QString>

//#include "quaa.h"

class QUaaUserInfo
{
    //! Only instance of QUaa is able to set token value for QUaaUserInfo
//    friend QUaa;

public:
    QUaaUserInfo();

    QString code() const;
    void setCode(const QString &code);

    QString login() const;
    void setLogin(const QString &login);

    QString password() const;
    void setPassword(const QString &password);

private:
    QString mLogin;
    QString mPassword;
    QString mCode;
    bool mIsActivated;
};

#endif // QUAAUSERINFO_H
