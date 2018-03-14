![LOGO](https://github.com/IndeemaSoftware/QPredix/blob/Assets/sdk_3_transparent.png?raw=true)

<h1 align="center"><img src="https://github.com/IndeemaSoftware/QPredix/blob/Assets/sdk_3_transparent.png" /><br> Driver.js</h1>

<p align="center">
  <a href="https://github.com/kamranahmedse/driver.js/blob/master/license">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" />
  </a>
</p>

<p align="center">
  <b>This is Qt/C++ SDK for Predix Ge services API (https://www.predix.io/) developed by [Indeema Software Inc.](https://indeema.com/). </b></br>
  <sub>It works for MacOS, Linux and Windows operation systems. <sub>
</p>

<br />

# QPredix
This is Qt/C++ SDK for Predix Ge services API (https://www.predix.io/) developed by [Indeema Software Inc.](https://indeema.com/). It works for MacOS, Linux and Windows operation systems.

## Documentation
## Minimum requirements
Qt 5.8

### Installing with qpm
Just use qpm (https://www.qpm.io/) to install QPredix in your project.
Run qpm install com.indeema.QPredix . in *.pro file include(vendor/Vendor.pri)

### How to start
A simple example you can find in [QPredixSamples folder](https://github.com/IndeemaSoftware/QPredixSample). 

Or copy QPredix folder to your project and add 

  include(...QPredix.pri) 

to your project *.pro file. Then we need to initialize it with QUaaInfo:

    QUaaInfo lInfo;
    lInfo.setUaaUrl("your UaaUrl taken from Predix Uaa service");
    lInfo.setClientCredential("Client id", "secret");

Then setup user with QUaaUserInfo:

    QUaaUserInfo lUser;
    lUser.setLogin("user credentials");
    lUser.setPassword("user password");
    
now you can start using Uaa service:

    QUaa *mUaa = new QUaa(lInfo);
    connect(mUaa, SIGNAL(loginSucced(QUaa*)), this, SLOT(loginSucceed()));
    mUaa->loginWithCredentials(lUser);

don't forget to initialize loginSucceed() slot;

After login is succeed you are able to start using TimeSeries service provided by Prexid:

    QTimeSeries *mTimeSeries = new QTimeSeries(mUaa);
    mTimeSeries->setZoneID("Your zone ID");
    
Now ingest data to timeseries service:
    
    QMap<QString, QString> lAtt;
    lAtt.insert("vector", "x");
    mTimeSeries->sendData("TEST1", 2, 3, lAtt);
    
First parameter is tag name, the second is value, the third is quality and the third is custom attributes.
There is more simple way to ingest data iwth only tag and value with default quality 3 and without attributes:

    mTimeSeries->sendData("TEST1", "0");

**If device doesn't have connection to internet, all data is stored locally until connection will apear. After connection is available all local data is synced with server**

## Communication and Support
If you encounter an issue or you have any comments or propositions with using the QPredix library then you can reach us in several different ways:
- Having difficulties with using QPredix you can write at [Stackoverflow](https://stackoverflow.com/) or at [Predix forum](https://forum.predix.io/index.html). Don't forget about specifing the **QPredix** tag. You will be helped by the community of this resource or our specialists will help you with an answer.

- If you find a bug and want to tell us about it - specify it in the section [Issues](https://github.com/IndeemaSoftware/QPredix/issues).
In this section, we only consider bugs and ignore any questions relating to the support.

- For additional assistance with your project - please contact us at **support@indeema.com** and specify **QPredix** in the subject line.

- You can also follow our news at [@IndeemaSoftware](https://twitter.com/IndeemaSoftware) or on our [blog](https://indeema.com/blog).

- For further questions on cooperation, simply email us at **support@indeema.com**.

## License
**QPredix** works under the MIT license. For more information see [here](https://github.com/IndeemaSoftware/QPredix/blob/master/LICENSE).

## Terms
**QPredix** is released for testing purposes only. We make no guarantees with respect to its function. By using this software you agree that Indeema is not liable for any damage to your system and data.
