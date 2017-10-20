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

#ifndef QPREDIXCORE_H
#define QPREDIXCORE_H

#include <QObject>
#include <QNetworkRequest>
#include <QSslError>
#include <QAuthenticator>

/** @file */

/**Undefined value for strings*/
#define UNDEFINED "-1"

/**By default we are using "v1" version of API*/
#define DEFAULT_API_VERSION "v1"

class QNetworkReply;
class QNetworkAccessManager;

/*! \class QPredixCore
    \brief Basic class for any Predix class that uses Uaa and communicates with Predix APIs

    \details To start using Uaa QPredixCore can save you time as it contains methods for request formation QNetworkRequest request(QUrl url);
    request manager and url parsers to know request name.
*/

class QPredixCore : public QObject
{
    Q_OBJECT
public:
    //! This constructor saves basic Predix API url and initializes QNetworkAccessManager object
    /*!
        \param url basic url to predix service
        \param cred client credentials decoded in base64 in format "client_id:secret"
        \param parent parent object
    */
    explicit QPredixCore(QString url, QString cred, QObject *parent = 0);
    ~QPredixCore();

    //! Basic Predix API url
    QString url() const;
    //! Sets basic Predix API url
    void setUrl(const QString &url);


    //! Decoded client_id from clientCredentials
    /*!
        \return string value of client_id from "client_id:secret"
    */
    QString clientId();
    //! Decoded secret from clientCredentials
    /*!
        \return string value of secret from "client_id:secret"
    */
    QString secret();

    //! Client credentials decoded with base64 in format "client_id:secret"
    /*!
        \return base64 of "client_id:secret"
    */
    QString clientCredentials() const;

    //! Client credentials decoded with base64 in format "client_id:secret"
    //! This variable is used for app authentication is Predix syste. Clint id and secret could be
    //! created in Predix user console.
    /*!
    */

    void setClientCredentials(const QString &clientCredentials);

    //! Version of API. By default the value os "v1"
    /*!
        \return API version
    */
    QString APIVersion() const;
    //! Sets vertion of API to use
    /*!
    */
    void setAPIVersion(const QString &aPIVersion);

protected:
    //! Forms url from base url (set in class constructor) + method url
    /*!
        \return is used to simplify process of url creation
    */
    QString formUrl(QString url);
    //! Forms url from base url (set in class constructor) + API version + method url
    /*!
        \return is used to simplify process of url creation
    */
    QString formUrl(QString url, QString version);

protected slots:
    //! Pure virtual slot that should be implemented in child class. This slot is connected to signal of QNetworkAccessManager object
    /*!
    */
    virtual void authenticationRequired(QNetworkReply *, QAuthenticator *) = 0;
    //! Pure virtual slot that should be implemented in child class this slot is connected to signal of QNetworkAccessManager object
    /*!
    */
    virtual void sslErrors(QNetworkReply *, const QList<QSslError> &) = 0;
    //! Pure virtual slot that should be implemented in child class this slot is connected to signal of QNetworkAccessManager object
    /*!
    */
    virtual void handleResponse(QNetworkReply *) = 0;

protected:
    //! QNetworkAccessManager object
    /*!
        \return QNetworkAccessManager object to REST API requests
    */
    QNetworkAccessManager *mgr() const;
    //! Returns version of API. By default it's "v1"
    /*!
        \return QString of API version. By default "v1"
    */
    QString getVersion(QNetworkReply*);
    //! Takes method name to clasify request
    /*!
        \return QString of request method
    */
    QString getCommand(QNetworkReply*);
    //! Forms request with standart headers
    /*!
        \return QNetworkRequest with prefilled headers
    */
    QNetworkRequest request(QUrl url);
    //! Server url for provided API version
    /*!
        \return Server url for provided API version
    */
    QByteArray serverUrl(QByteArray version);


private:
    QNetworkAccessManager* mMgr;
    QString mUrl;
    QString mClientCredentials;
    QString mAPIVersion;
};

#endif // QPREDIXCORE_H
