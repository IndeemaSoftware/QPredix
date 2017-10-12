#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../QPredix/qpredix.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTimeSeries{nullptr}
{
    ui->setupUi(this);

    QUaaInfo lInfo;
    lInfo.setUaaUrl("your UaaUrl taken from Predix Uaa service");
    lInfo.setBase64ClientCredential("Your credenticals in base64 in format \"client_id:secret\"");

    QUaaUserInfo lUser;
    lUser.setLogin("user credentials");
    lUser.setPassword("user password");

    mUaa = new QUaa(lInfo);
    connect(mUaa, SIGNAL(loginSucceed(QUaa*)), this, SLOT(loginSucced()));
    mUaa->loginWithCredentials(lUser);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (mTimeSeries != nullptr) {
        delete mTimeSeries;
    }

    delete mUaa;
}

void MainWindow::loginSucced()
{
    qDebug() << __FUNCTION__;
    mTimeSeries = new QTimeSeries(mUaa);
    mTimeSeries->setZoneID("Your zone ID");

//    QStringList lAttributes;
//    lAttributes.append("test");

//    QList<double> lQualities;
//    lQualities.append(3);

//    QList<double> lValues;
//    lValues.append(36);

//    QTimeSeriesMeasurements lMes;
//    lMes.setCondition("First");
//    lMes.setValues(lValues);

//    QTimeSeriesTag lTag;
//    lTag.setName("Test_sensor");
//    lTag.setSuppressGroupByType(false);
//    lTag.setAttributes(lAttributes);
//    lTag.setQualities(lQualities);
//    lTag.setMeasurements(lMes);

//    QList<QTimeSeriesTag> lTags;
//    lTags.append(lTag);

//    QStringList lList;
//    lList.append("TEST");

//    mTimeSeries->getTags();
//    mTimeSeries->getLatestDatapoints(lList);

//    mTimeSeries->sendCustomRequest("{start: 1y-ago,tags: [ {name: TEST,order: desc,limit: 3 } ] }");

//    mTimeSeries->getLimitedDatapoints(lList, 5);
//    mTimeSeries->getFromToDatapoints(lList, "1152112200000", "2052112200000");
//    mTimeSeries->openSocket();

    mTimeSeries->sendData("123", "HELLO");
}
