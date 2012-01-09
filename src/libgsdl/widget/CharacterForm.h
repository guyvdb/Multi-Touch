#ifndef CHARACTERFORM_H
#define CHARACTERFORM_H

#include <QFrame>
#include <QVariantMap>
#include <QWebView>

#include "ast/GameSystem.h"


namespace gsdl {

  class CharacterForm : public QFrame
  {
      Q_OBJECT
  public:
    explicit CharacterForm(const QString fileName, QVariantMap &character,  GameSystem *gameSystem, QWidget *parent = 0);
  protected:
    void resizeEvent(QResizeEvent *);

  private slots:
    void OnPageLoaded(bool flag);
  private:
    QWebView *view;
    QVariantMap &character;
    GameSystem *gameSystem;

  };

}

#endif // CHARACTERFORM_H
