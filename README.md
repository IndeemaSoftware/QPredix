![LOGO](https://github.com/IndeemaSoftware/QPredix/blob/Assets/indeema_logo.jpg?raw=true)

# QPredix
This is Qt/C++ SDK for Predix Ge services API (https://www.predix.io/) developed by [Indeema Software Inc.](https://indeema.com/). It works for MacOS, Linux and Windows operation systems.

## Documentation
### How to start
A simple example you can find in [QPredixSamples folder](https://github.com/IndeemaSoftware/QPredix/tree/master/QPredixSamples). 

Copy QPredix folder to your project and add 

  include(QPredix.pri) 

to your project *.pro file. Then we need to initialize it with QUaaInfo:

    QUaaInfo lInfo;
    lInfo.setUaaUrl("your UaaUrl taken from Predix Uaa service");
    lInfo.setBase64ClientCredential("Your credenticals in base64 in format \"client_id:secret\"");

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
