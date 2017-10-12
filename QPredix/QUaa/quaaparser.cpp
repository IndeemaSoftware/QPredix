#include "quaaparser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#define KEY_TOKEN       "access_token"
#define KEY_TOKEN_TYPE  "token_type"
#define KEY_REFRESH_TOKEN "refresh_token"
#define KEY_EXPIRES     "expires_in"
#define KEY_SCOPE       "scope"
#define KEY_JTI         "jti"

QUaaParser::QUaaParser()
{

}

QUaaSessionInfo QUaaParser::parseUaaLoginResponse(QByteArray jsonData)
{
    QUaaSessionInfo rSession;

    QJsonDocument lJsonDoc = QJsonDocument::fromJson(jsonData);
    if (lJsonDoc.isObject()) {
        QJsonObject lJson(lJsonDoc.object());

        rSession.setToken(lJson.value(KEY_TOKEN).toString());
        rSession.setTokenType(lJson.value(KEY_TOKEN_TYPE).toString());
        rSession.setRefreshToken(lJson.value(KEY_REFRESH_TOKEN).toString());
        rSession.setExpiresIn(lJson.value(KEY_EXPIRES).toInt());

        QStringList lScope;
        for (QString value : lJson.value(KEY_SCOPE).toString().split(" ")) {
            lScope.append(value);
        }
        rSession.setScope(lScope);
        rSession.setJti(lJson.value(KEY_JTI).toString());

    } else {
        qDebug() << "Data received is not JSON Object";
    }

    return rSession;
}
