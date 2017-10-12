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

#ifndef QTIMESERIES_GLOBAL_H
#define QTIMESERIES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTIMESERIES_LIBRARY)
#  define QTIMESERIESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTIMESERIESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTIMESERIES_GLOBAL_H
