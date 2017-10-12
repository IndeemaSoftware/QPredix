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

#ifndef QUAA_H
#define QUAA_H

#include "quaa_global.h"
#include "quaainfo.h"
#include "quaauserinfo.h"
#include "quaasessioninfo.h"

#include <QObject>

class QUaaRequests;
class QTimer;

//!  QUaa is starting point to use Predix Uaa service
/*!
    To be able to use Uaa service, please start service on Predix console and copy service UaaUrl and create client_id and secret for it. Secret can't be changed so remember it when creating.
*/


class QUAASHARED_EXPORT QUaa : public QObject
{
    Q_OBJECT
public:
    //!This costructor defines basis auth parameters like client authentication
    /*!
        \param uaaInfo basic client cretentials (url and decoded "client_id:secret" with base64)
        \param parent parent object
    */
    explicit QUaa(QUaaInfo uaaInfo, QObject *parent=0);
    ~QUaa();

    //!Implementes user login functionality to predix Uaa service. After login is succesfull token and refresh token are saved in uaaUserInfo object. Token is refreshed with expires_in time
    /*!
        \param userInfo variable with login and password
    */
    void loginWithCredentials(QUaaUserInfo userInfo);

    //!Implementes user login functionality to predix Uaa service. After login is succesfull token and refresh token are saved in uaaUserInfo object. Token is refreshed with expires_in time
    /*!
        \return QUaa
    */
    QUaaInfo uaaInfo() const;
    void setUaaInfo(const QUaaInfo &uaaInfo);

    QUaaUserInfo uaaUserInfo() const;

    QUaaSessionInfo userSessionInfo() const;

    QUaaSessionInfo clientSessionInfo() const;

private:
    bool isUaaSetup();
    void startRefreshTimer();

signals:
    void loginSucceed(QUaa*);
    void loginFailed(QString);

private slots:
    void refreshToken();
    void loginSucceed(QUaaSessionInfo);

private:
    QUaaUserInfo mUaaUserInfo;
    QUaaSessionInfo mUserSessionInfo;
    QUaaSessionInfo mClientSessionInfo;
    QUaaInfo mUaaInfo;

    QUaaRequests *mRequest;
    QTimer *mRefreshTokenTimer;
};

#endif // QUAA_H
