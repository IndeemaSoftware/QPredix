#ifndef QUAAPARSER_H
#define QUAAPARSER_H

#include "quaasessioninfo.h"

class QUaaParser
{
public:
    QUaaParser();

static QUaaSessionInfo parseUaaLoginResponse(QByteArray);

};

#endif // QUAAPARSER_H
