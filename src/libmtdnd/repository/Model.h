#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVariant>

namespace mtdnd {

  class Model;

  class MetaField {
    QByteArray name;
    QVariant::Type type;
    bool autoIncrement;
    bool index;
    int maxLength;
    bool unique;
    QString foreignModel;
  };

  class MetaModel {
    MetaModel(const Model *model);
    bool isValid();
    bool createTable() const;
    bool dropTable() const;
    void load(Model *model, const QVariantList &props, int &pos) const;
    bool remove(Model *model) const;
    bool save(Model *model) const;

    QObject *getForeignKey(const Model *model, const char *name) const;
    void setForeignKey(Model *model, const char *name, QObject *value) const;
  };


  class Model : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QVariant pk READ getPk WRITE setPk)
  public:
    explicit Model(QObject *parent = 0);
    QVariant getPk() const;
    void setPk(const QVariant &pk);

  public slots:
    bool remove();
    bool save();
    QString toString() const;

  protected:
    QObject *getForeignKey(const char *name) const;
    void setForeignKey(const char *name, QObject *value);

  signals:

  public slots:

  };

}

#endif // MODEL_H
