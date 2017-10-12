#ifndef QTIMESERIESCOMMANDS_H
#define QTIMESERIESCOMMANDS_H

#define QTS_URL "https://time-series-store-predix.run.aws-usw02-pr.ice.predix.io"
#define QTS_CMD_DATAPOINTS "/datapoints"
#define QTS_CMD_LATEST "/datapoints/latest"
#define QTS_CMD_TAGS "/tags"

#define TS_KEY_RESULTS "results"
#define TS_WEBSOCKET_URL QStringLiteral("wss://gateway-predix-data-services.run.aws-usw02-pr.ice.predix.io/v1/stream/messages")
#define TS_WEBSOCKET_ORIGIN QStringLiteral("http://localhost")

#endif // QTIMESERIESCOMMANDS_H
