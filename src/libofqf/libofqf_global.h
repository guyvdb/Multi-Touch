#ifndef LIBOFQF_GLOBAL_H
#define LIBOFQF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBOFQF_LIBRARY)
#  define LIBOFQF__EXPORT Q_DECL_EXPORT
#else
#  define LIBOFQF__EXPORT Q_DECL_IMPORT
#endif

#endif // LIBOFQF_GLOBAL_H
