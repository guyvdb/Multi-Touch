#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <QObject>
#include <QtScript/QScriptEngine>

#include "libmtg_global.h"

namespace mtdnd {

  class LIBMTDND_EXPORT GameSystem : public QObject
  {
      Q_OBJECT
  public:
    explicit GameSystem(QObject *parent = 0);


    bool load(const QString fileName);

  private:
    QScriptEngine *interpreter;

  };

}

#endif // GAMESYSTEM_H
