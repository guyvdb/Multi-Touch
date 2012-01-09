#ifndef TOKEN_H
#define TOKEN_H

#include "libgsdl_global.h"

#include <QObject>
#include <QStringList>

namespace gsdl {

  class LIBGSDL_EXPORT Token : public QObject
  {
      Q_OBJECT
  public:
    explicit Token(QObject *parent = 0);
    QStringList* getErrors() {return &this->errors; }
  protected:
    void addError(const QString error) {this->errors.append(error); }
  private:
    QStringList errors;
  };

}

#endif // TOKEN_H
