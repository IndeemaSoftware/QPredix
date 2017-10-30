#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../QPredix/qpredix.h"

#include <QDebug>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mTimeSeries{nullptr}
{
  ui->setupUi(this);

  QUaaInfo lInfo;
  lInfo.setUaaUrl("https://a3fe4c03-fa0b-4f78-bc33-67df00f5cdf5.predix-uaa.run.aws-usw02-pr.ice.predix.io");
  lInfo.setBase64ClientCredential("bG9naW5fY2xpZW50X2lkOnF3ZXJ0eTEyMw==");

  QUaaUserInfo lUser;
  lUser.setLogin("app_user_1");
  lUser.setPassword("qwerty123");

  mUaa = new QUaa(lInfo);
  connect(mUaa, SIGNAL(loginSucceed(QUaa*)), this, SLOT(loginSucced()));
  mUaa->loginWithCredentials(lUser);

  mTimeSeries = new QTimeSeries(mUaa);
  mTimeSeries->setZoneID("5e5d076e-c8df-4340-a9b3-7e5c0a1386ef");

  mTimeSeries->sendData("TEST1", "1", "1", QString("{\"vector\": \"y\"}"));
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

  mTimeSeries->sendData("TEST1", "2", "2", QString("{\"vector\": \"x\"}"));
}
