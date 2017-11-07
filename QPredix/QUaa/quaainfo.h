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

#ifndef QUAAINFO_H
#define QUAAINFO_H

#include <QString>

//!  QUaaInfo is a container class that holds all the details regarding Uaa account
/*!
  To start using Uaa service you should create instance of QUaaInfo and set uaaUrl (you can get it in your Predix console) and set base64ClientCredential and loginBase64ClientCredential
*/

class QUaaInfo
{
public:
    //! Default constructor
    QUaaInfo();
    QUaaInfo(QUaaInfo *info);

    bool isValid();

    //! Uaa url is used for Predix secude authentication. You can get it at Predix personal console
    /*!
        \return return value is Uaa url
    */
    QString uaaUrl() const;
    //! UaaUrl sets url to Uaa service. To get uaa service go to predix personal console
    /*!
        uaaUrl is Predix url for Uaa service
    */
    void setUaaUrl(const QString &uaaUrl);

    //! base64ClientCredential is set of credentials used for Predix secude authentication. You can get it at Predix personal console
    /*!
        base64ClientCredential is stored in base64 decoding in format "client_id:secure". It is used for data posting to Predix server
        \return return value is base64 decode of "client_id:secure"
    */
    QString base64ClientCredential() const;

    //! base64ClientCredential is set of credentials used for Predix secude authentication. You can get it at Predix personal console
    /*!
      base64ClientCredential is used for data posting to Predix server
        \param base64ClientCredential should be base64 in format "client_id:secure". You can decode your credantials here - http://www.utilities-online.info/base64/.
    */
    void setBase64ClientCredential(const QString &base64ClientCredential);

    //! By using this method you set credentials to login as client and star using service
    /*! later these credentials are encoded with base64 in format client_id:secret and storred in base64ClientCredential
        \param login client login id
        \param secret password used for client id
    */
    void setClientCredential(const QString &login, const QString secret);

private:
    void checkCredentials();

private:
    QString mUaaUrl;
    QString mBase64ClientCredential;
};

#endif // QUAAINFO_H
