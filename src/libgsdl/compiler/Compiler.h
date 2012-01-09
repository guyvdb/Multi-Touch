#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include "ast/GameSystem.h"

namespace gsdl {

  class Compiler : public QObject
  {
      Q_OBJECT
  public:
    explicit Compiler(QObject *parent = 0);
    GameSystem* compile(const QString filename);
  };

}

#endif // COMPILER_H
