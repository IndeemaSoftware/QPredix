#ifndef QUAA_GLOBAL_H
#define QUAA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QUAA_LIBRARY)
#  define QUAASHARED_EXPORT Q_DECL_EXPORT
#else
#  define QUAASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QUAA_GLOBAL_H
