#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QObject>
#include <QList>

#include "GameToken.h"

#include "libmtg_global.h"

namespace mtg {

  class LIBMTG_EXPORT  GameTokens : public QObject
  {
      Q_OBJECT
  public:
    explicit GameTokens();
    GameToken* add(GameToken* token);
    GameToken* add(mtg::GameToken::Type type);
    void remove(GameToken *token);
    void remove(const int id);
    void clear();
    GameToken *find(const int id);
    bool isTokenAtLocation(QPoint &location);
    GameToken *tokenAtLocation(QPoint &location);
    QList<GameToken*> & list() {return this->tokens;}
    void getMapTokens(QList<MapToken*> &result);
  private:
    QList<GameToken*> tokens;
    int nextId;
  signals:

  public slots:

  };

}

#endif // TOKENLIST_H
