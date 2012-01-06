
#include "Map.h"

namespace mtdnd {
  Map::Map(QObject *parent) : Model(parent) {

  }

  QString Map::getName() const {
    return this->name;
  }

  void Map::setName(const QString value) {
    this->name = value;
  }

  QString Map::getFile() const {
    return this->file;
  }

  void Map::setFile(const QString value) {
    this->file = value;
  }
}
