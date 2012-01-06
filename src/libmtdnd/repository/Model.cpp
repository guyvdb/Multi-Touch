#include "Model.h"

namespace mtdnd {

  Model::Model(QObject *parent) : QObject(parent) {
  }

  QVariant Model::getPk() const {
    //const MetaModel meta = Repo
  }

  void Model::setPk(const QVariant &pk) {

  }

  bool Model::save() {

  }

  bool Model::remove() {

  }

  QString Model::toString() const {

  }

  QObject *Model::getForeignKey(const char *name) const {

  }

  void Model::setForeignKey(const char *name, QObject *value) {

  }

}
