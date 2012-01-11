#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <QObject>
#include <QtScript/QScriptEngine>

#include "librpg_global.h"

namespace rpg {

  class LIBRPG_EXPORT GameSystem : public QObject
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
