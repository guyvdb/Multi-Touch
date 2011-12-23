#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QObject>
#include <QList>

#include "Token.h"

namespace mtg {

  class GameTokenList : public QObject
  {
      Q_OBJECT
  public:
      explicit GameTokenList();


  private:
    QList<GameToken*> tokens;

  signals:

  public slots:

  };

}

#endif // TOKENLIST_H
