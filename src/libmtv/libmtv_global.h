#ifndef LIBMTV_GLOBAL_H
#define LIBMTV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBMTV_LIBRARY)
#  define LIBMTV_EXPORT Q_DECL_EXPORT
#else
#  define LIBMTV_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBMTV_GLOBAL_H
