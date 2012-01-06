#ifndef DOCKLIST_H
#define DOCKLIST_H

#include <QFrame>
#include <QList>
#include <QToolButton>
#include <QIcon>
#include <QListWidget>


class DockListWidgetItem : public QListWidgetItem {
public:
  DockListWidgetItem(QVariantMap map, const QString text, QListWidget * parent = 0) : QListWidgetItem(text,parent), map(map) {}
  QVariantMap &getMap() {return this->map; }
private:
  QVariantMap map;
};


class DockListWidget : public QFrame
{
    Q_OBJECT
public:
  explicit DockListWidget(QWidget *parent = 0);
  QToolButton* addButton(QIcon icon, const QString tooltip, const QObject *receiver, const char *slot, bool defaultAction);
  QToolButton* addButton(const QString tooltip, const QObject *receiver, const char *slot, bool defaultAction);

  void disable();
  void enable();
  void populate(QList<QVariantMap> items, const char * key);
  bool hasSelection();
  DockListWidgetItem* selectedItem() const;
signals:
  void clicked();
private slots:
 void OnListDoubleClicked(QModelIndex);
protected:
  QToolButton* addButton(QIcon *icon, const QString tooltip, const QObject *receiver, const char *slot, bool defaultAction = false);

  virtual void resizeEvent(QResizeEvent *);

private:
  QList<QToolButton*> buttons;
  QListWidget *list;


};

#endif // DOCKLIST_H
