/***************************************************************************
 *                                                                         *
 *   This Predix services API was created by by Indeema Software Inc.      *
 *   QPredix SDK is under MIT license so you are free to use it.           *
 *   https://indeema.com                                                   *
 *                                                                         *
 *   In case if you have any issues or comments, please conntact us:       *
 *   support@indeema.com                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QUAAUSERINFO_H
#define QUAAUSERINFO_H

#include <QString>

class QUaaUserInfo
{
    //! Only instance of QUaa is able to set token value for QUaaUserInfo

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
};

#endif // QUAAUSERINFO_H
