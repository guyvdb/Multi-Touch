#ifndef CHARACTERFORM_H
#define CHARACTERFORM_H

#include <QFrame>
#include <QVariantMap>
#include <QWebView>
#include <QWebElement>

#include "ast/GameSystem.h"

#include "Bridge.h"


namespace character {

  class CharacterForm : public QFrame
  {
      Q_OBJECT
  public:
    explicit CharacterForm(const QString fileName, QVariantMap &character, gsdl::GameSystem *gameSystem, QWidget *parent = 0);
  protected:
    void resizeEvent(QResizeEvent *);

  private slots:
    void OnLoadJSObject();
    void OnPageLoaded(bool flag);

  private:

    void addField(QWebElement &element, const QString fieldName);
    QString buildSimpleField(gsdl::Field *metaField, QWebElement &element, const QString fieldName);

    QWebView *view;
    QVariantMap &character;
    gsdl::GameSystem *gameSystem;
    Bridge *bridge;

  };

}

#endif // CHARACTERFORM_H
