#include "CharacterForm.h"
#include <QUrl>
#include <QDebug>
#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>

namespace gsdl {

  CharacterForm::CharacterForm(const QString fileName, QVariantMap &character,  GameSystem *gameSystem, QWidget *parent)
    : QFrame(parent), character(character), gameSystem(gameSystem)
  {
    this->view = new QWebView(this);

    QUrl url("file://" + fileName);
    this->view->load(url);
    qDebug() << url;
    this->connect(this->view, SIGNAL(loadFinished(bool)), this, SLOT(OnPageLoaded(bool)));
    this->view->show();

  }

  void CharacterForm::resizeEvent(QResizeEvent *) {
    this->view->setGeometry(QRect(10,10,this->width()-20,this->height()-20));
  }

  void CharacterForm::OnPageLoaded(bool flag) {
    QWebFrame *frame = this->view->page()->mainFrame();

    qDebug() << frame->documentElement().toPlainText();

    QWebElement document = frame->documentElement();

    QWebElementCollection fields = document.findAll("field");


    qDebug() << "COUNT: " << fields.count();

    qDebug() << "--------------------- BEFORE";
    qDebug() << document.toInnerXml();

    for(int i=fields.count()-1; i >=0; i--){
      QWebElement el = fields.at(i);
      QString data = el.attribute("name");
      QString name(data);
      name.replace(" ","_");
      QString clazz = el.attribute("class");
      QString html = "<input type=\"text\" name=\"" + name + "\" data-field-name=\"" + data + "\" class=\"" + clazz + "\" />";
      el.replace(html);


    }
qDebug() << "--------------------- AFTER";
    qDebug() << document.toInnerXml();

    /*
    QWebElement document = frame->documentElement();
        Assume the document has the following structure:

          <p class=intro>
            <span>Intro</span>
            <span>Snippets</span>
          </p>
          <p>
            <span>Content</span>
            <span>Here</span>
          </p>


       QWebElementCollection allSpans = document.findAll("span");
       QWebElementCollection introSpans = document.findAll("p.intro span");
       */


  }

}
