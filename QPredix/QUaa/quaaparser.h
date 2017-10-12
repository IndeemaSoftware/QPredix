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
