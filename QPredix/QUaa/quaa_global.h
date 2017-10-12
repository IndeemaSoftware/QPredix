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

#ifndef QUAA_GLOBAL_H
#define QUAA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QUAA_LIBRARY)
#  define QUAASHARED_EXPORT Q_DECL_EXPORT
#else
#  define QUAASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QUAA_GLOBAL_H
