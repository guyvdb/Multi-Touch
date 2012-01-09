#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include "ast/GameSystem.h"


#include "libgsdl_global.h"

namespace gsdl {

  class LIBGSDL_EXPORT Compiler : public QObject
  {
      Q_OBJECT
  public:
    explicit Compiler(QObject *parent = 0);
    GameSystem* compile(const QString filename);
  };

}

#endif // COMPILER_H
