#ifndef ITEM_H
#define ITEM_H

#include "libgsdl_global.h"
#include "ast/Token.h"

namespace gsdl {

  class LIBGSDL_EXPORT Item : public Token
  {
      Q_OBJECT
  public:
    explicit Item(const QString name, QObject *parent = 0);
    QString getName() const {return this->name;}
    void setValue(const QString value) {this->value = value; }
    QString getValue() const {return this->value; }
  private:
    QString name;
    QString value;


  };

}

#endif // ITEM_H
