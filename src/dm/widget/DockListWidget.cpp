#include "DockListWidget.h"

DockListWidget::DockListWidget(QWidget *parent) : QFrame(parent)
{
  this->list = new QListWidget(this);
  this->connect(this->list,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OnListDoubleClicked(QModelIndex)));
}


QToolButton* DockListWidget::addButton(QIcon icon, const QString tooltip,const QObject *receiver, const char *slot, bool defaultAction) {
  return this->addButton(&icon,tooltip,receiver,slot,defaultAction);
}

QToolButton* DockListWidget::addButton(const QString tooltip,const QObject *receiver, const char *slot, bool defaultAction) {
  return this->addButton(0x0,tooltip,receiver,slot,defaultAction);
}

QToolButton* DockListWidget::addButton(QIcon *icon, const QString tooltip, const QObject *receiver, const char *slot, bool defaultAction) {
  QToolButton *button = new QToolButton(this);
  button->setToolTip(tooltip);
  button->setStatusTip(tooltip);
  if(icon != 0x0) button->setIcon(*icon);
  this->connect(button,SIGNAL(clicked()),receiver,slot);
  if(defaultAction) {
    this->connect(this,SIGNAL(clicked()), receiver, slot);
  }
  this->buttons.append(button);
  return button;
}

void DockListWidget::disable() {
  this->list->setDisabled(true);
  foreach (QToolButton *button, this->buttons) button->setDisabled(true);
}

void DockListWidget::enable() {
  this->list->setEnabled(true);
  foreach (QToolButton *button, this->buttons) button->setEnabled(true);
}

void DockListWidget::populate(QList<QVariantMap> items, const char * key) {
  this->list->clear();
  foreach(QVariantMap item, items) {
    DockListWidgetItem *i = new DockListWidgetItem(item, item.value(key).toString(), this->list);
    this->list->addItem(i);
  }
}

bool DockListWidget::hasSelection() {
  return (this->list->selectedItems().count() != 0);
}

DockListWidgetItem* DockListWidget::selectedItem() const {
  if(this->list->selectedItems().count() == 0) return 0x0;
  QListWidgetItem *item =  this->list->selectedItems().at(0);
  return (DockListWidgetItem*)item; // should be doing a safe cast
}

void DockListWidget::resizeEvent(QResizeEvent *) {
  int top;
  int left;
  top = 0;
  left = 0;

  foreach(QToolButton *button, this->buttons) {
    button->setGeometry(left,top,21,21);
    left += 21;
  }

  top = 22;
  left = 0;
  this->list->setGeometry(left,top,this->width(),this->height()-top);
}

void DockListWidget::OnListDoubleClicked(QModelIndex) {
  emit clicked();
}
