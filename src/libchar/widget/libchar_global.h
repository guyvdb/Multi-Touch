#ifndef LIBCHAR_GLOBAL_H
#define LIBCHAR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBCHAR_LIBRARY)
#  define LIBCHAR_EXPORT Q_DECL_EXPORT
#else
#  define LIBCHAR_EXPORT Q_DECL_IMPORT
#endif


#endif // LIBCHAR_GLOBAL_H
