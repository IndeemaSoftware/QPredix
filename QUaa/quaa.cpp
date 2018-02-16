#include "quaa.h"
#include "quaacommands.h"
#include "quaaparser.h"
#include "quaarequests.h"

#include <QTimer>

#include <QDebug>

QUaa::QUaa(QUaaInfo info, QObject *parent) : QObject(parent)
{
    mUaaInfo = info;

    mRefreshTokenTimer = new QTimer(this);
    connect(mRefreshTokenTimer, SIGNAL(timeout()), this, SLOT(refreshToken()));

    mRequest = new QUaaRequests(mUaaInfo.uaaUrl(), mUaaInfo.base64ClientCredential());
    connect(mRequest, SIGNAL(loginSucceed(QUaaSessionInfo)), this, SLOT(loginSucceed(QUaaSessionInfo)));
    connect(mRequest, SIGNAL(loginFailed(QString)), this, SIGNAL(loginFailed(QString)));
}

QUaa::~QUaa()
{
    if (mRefreshTokenTimer->isActive()) {
        mRefreshTokenTimer->stop();
    }

    delete mRefreshTokenTimer;
    delete mRequest;
}

void QUaa::loginWithCredentials(QUaaUserInfo userInfo)
{
    qDebug() << __FUNCTION__;
    mUaaUserInfo = userInfo;

    if (isUaaSetup()) {
        mRequest->loginUser(mUaaUserInfo.login(), mUaaUserInfo.password());
    }
}

QUaaInfo QUaa::uaaInfo() const
{
    return mUaaInfo;
}

void QUaa::setUaaInfo(const QUaaInfo &uaaInfo)
{
    mUaaInfo = uaaInfo;
}

QUaaUserInfo QUaa::uaaUserInfo() const
{
    return mUaaUserInfo;
}

bool QUaa::isUaaSetup()
{
    bool rIsSetup = true;

    if (!mUaaInfo.isValid()) {
        rIsSetup = false;

        qDebug() << "Uaa url or credentials were not set. Please add Uaa url and credentials in format \"client_id:secret\" in base64";
    }

    return rIsSetup;
}

void QUaa::startRefreshTimer()
{
    qDebug() << __FUNCTION__;
    qDebug() << "Token file time: " << mUserSessionInfo.expiresIn();
    mRefreshTokenTimer->setInterval(1000*mUserSessionInfo.expiresIn());
    mRefreshTokenTimer->start();
}

void QUaa::refreshToken()
{
    qDebug() << __FUNCTION__;
    mRequest->refreshToken(mUserSessionInfo.refreshToken());
}

void QUaa::loginSucceed(QUaaSessionInfo sessionInfo)
{
    if (mUserSessionInfo.token().isEmpty()) {
        mUserSessionInfo = sessionInfo;//saving user session details
        startRefreshTimer();
        mRequest->loginClient();
    } else {
        mClientSessionInfo = sessionInfo;//saving client session details

        emit loginSucceed(this); //only after we have client credentials signal is emmited
    }
}

QUaaSessionInfo QUaa::clientSessionInfo() const
{
    return mClientSessionInfo;
}

QUaaSessionInfo QUaa::userSessionInfo() const
{
    return mUserSessionInfo;
}
