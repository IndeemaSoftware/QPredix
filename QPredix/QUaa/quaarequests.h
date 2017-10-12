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

#ifndef QUAAREQUESTS_H
#define QUAAREQUESTS_H

#include "quaasessioninfo.h"

#include "../QPredixCore/qpredixcore.h"

class QNetworkAccessManager;

class QUaaRequests : public QPredixCore
{
    Q_OBJECT
public:
    QUaaRequests(QString url, QString cred, QPredixCore *parent = 0);

    void loginUser(QString userName, QString password);
    void loginClient();
    void refreshToken(QString tokenRefresh);

signals:
    void loginSucceed(QUaaSessionInfo);

protected slots:
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void handleResponse(QNetworkReply *reply);
};

#endif // QUAAREQUESTS_H
