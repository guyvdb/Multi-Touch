/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#ifndef LIBMTG_GLOBAL_H
#define LIBMTG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBMTG_LIBRARY)
#  define LIBMTG_EXPORT Q_DECL_EXPORT
#else
#  define LIBMTG_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBMTG_GLOBAL_H
