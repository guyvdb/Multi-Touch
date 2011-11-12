/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#ifndef LIBMT_GLOBAL_H
#define LIBMT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBMT_LIBRARY)
#  define LIBMT_EXPORT Q_DECL_EXPORT
#else
#  define LIBMT_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBMT_GLOBAL_H
