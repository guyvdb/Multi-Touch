#include "Item.h"

namespace gsdl {

  Item::Item(const QString name, QObject *parent) : Token(parent), name(name), value(name)
  {
  }

}
