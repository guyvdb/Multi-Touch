/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

/*
  Modules are chained into a pipeline. The pipeline must start with an OUTPUT only module and
  ends when an INPUT only module is encounted. All modules inbetween will be INPUT/OUTPUT modules.

  By default the modules are executed in parallel where possiable.  E.g:

                       F
                      / \
                C - E    | - H
              /         /
      A - B   \       /
                D - G

  So you map the output of one module to the input of the next. A module can have more that one input
  stream. But it should only generate one output stream.


 */

#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>

#include "libmtv_global.h"

namespace mtv {

  class LIBMTV_EXPORT Pipeline : public QObject
  {
      Q_OBJECT
  public:
      Pipeline(QObject *parent = 0);

  signals:

  public slots:

  };

}

#endif // PIPELINE_H
