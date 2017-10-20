#ifndef QTIMESERIES_H
#define QTIMESERIES_H
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

#include <QObject>
#include <QStringList>

class QUaa;
class QTimeSeriesRequests;

/*! \class QTimeSeries
    \brief This class is responsinble for any manipulation with Predix timeseries service

    \details To start working with timeseries you need to init QTimeSeries with instance of QUaa and set you unique zoneId. You can find you zone id in your Predix console
*/

class QTimeSeries : public QObject
{
    Q_OBJECT

public:
    //! This constructor saves initialized instance of QUaa, that is used for secure connection with Predix service
    /*!
        \param uaa instance of QUaa
        \param parent parent object
    */
    explicit QTimeSeries(QUaa* uaa, QObject *parent=0);
    ~QTimeSeries();

    //! By using sendCustomRequest(QString body) method you are able to form any query you need. Mostly it's used to for your custom filter, with custom attributes etc.
    //! as a responce user receives signal customRequestResponse(QByteArray)
    /*!
        \param body JSON body ofhttps://time-series-store-predix.run.aws-usw02-pr.ice.predix.io/datapoints query
    */
    void sendCustomRequest(QString body);

    //! By using getTags() you can get a list of all available tags on your timeserice zone
    //! as a responce user receives signal tagsList(QStringList)
    void getTags();

    //! By using getLatestDatapoints(QStringList) method you are able to get all latest data for given list of tags
    //! as a responce user receives signal latestDatapoints(QByteArray)
    /*!
        \param tags QStringList of tags. You can get list of tags by calling getTags()
    */
    void getLatestDatapoints(QStringList tags);

    //! By using getLimitedDatapoints(QStringList tags, int count) method you are able to get count of latest data for given list of tags.
    //! as a responce user receives signal customRequestResponse(QByteArray)
    /*!
        \param tags QStringList of tags. You can get list of tags by calling getTags()
        \param count number of data to get
    */
    void getLimitedDatapoints(QStringList tags, int count);

    //! By using getFromToDatapoints(QStringList tags, QString from, QString to) method you are able to get data for given list of tags for provided period from - to.
    //! as a responce user receives signal fromToDatapoints(QByteArray)
    /*!
        \param tags QStringList of tags. You can get list of tags by calling getTags()
        \param from starting data of period as timestamp in miliseconds
        \param to ending data of period as timestamp in miliseconds
    */
    void getFromToDatapoints(QStringList tags, QString from, QString to);

    //! To send data to Predix timeseries service you can use sendData(QString tagName, QString data, QString quality="3", QString attributes=nullptr)
    /*!
        \param tagName target tag name to send data to. You can get list of tags by calling getTags().
        \param data is unique data to store.
        \param quality this is quality of your data as int from 0 to 3, by default the value is 3.
        \param attributes json with attributes. For instance - {\"vector\": \"x\"}
        \code mTimeSeries->sendData("TEST1", "0", "0", QString("{\"vector\": \"x\"}"));
    */
    void sendData(QString tagName, QString data, QString quality="3", QString attributes=nullptr);

    //! Zone id is unique id of Predix timeseries service.
    /*!
      \return QString value of zone id
    */
    QString zoneID() const;

    //! To start using Pedix timeseries service you need to set aone id. Yopu can get it in your Predix console timeservice panel
    /*!
      \param zoneID value of zone id
    */
    void setZoneID(const QString &zoneID);

signals:
    //! List of tags
    void tagsList(QStringList tags);

    //! Latest datapoints in json format
    void latestDatapoints(QByteArray data);

    //! Response according to custom request in json format
    void customRequestResponse(QByteArray data);

    //! Limited datapoints in json format
    void limitedDatapoints(QByteArray data);

    //! Datapoints for specific period in json format
    void fromToDatapoints(QByteArray data);

private slots:
    //! Tags in json format
    void tagsReceived(QByteArray data);

private:
    QUaa *mUaa;
    QString mZoneID;
    QTimeSeriesRequests *mRequest;
};

#endif // QTIMESERIES_H
