#ifndef LIBGSDL_GLOBAL_H
#define LIBGSDL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBGSDL_LIBRARY)
#  define LIBGSDL_EXPORT Q_DECL_EXPORT
#else
#  define LIBGSDL_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBGSDL_GLOBAL_H
