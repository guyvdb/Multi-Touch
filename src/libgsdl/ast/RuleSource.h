#ifndef RULESOURCE_H
#define RULESOURCE_H

#include <QObject>

#include "libgsdl_global.h"
#include "ast/Token.h"

namespace gsdl {

  class LIBGSDL_EXPORT RuleSource : public Token
  {
    Q_OBJECT
  public:
    explicit RuleSource(const QString value, QObject *parent = 0);
    void setValue(const QString value) {this->value = value; }
    QString getValue() const {return this->value; }
  private:
    QString value;
  };

}
#endif // RULESOURCE_H
