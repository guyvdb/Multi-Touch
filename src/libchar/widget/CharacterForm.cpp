/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */

#include "CharacterForm.h"
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QWebFrame>
#include <QWebElementCollection>

#include "ast/Field.h"

namespace character {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CharacterForm::CharacterForm(QWidget *parent) : QFrame(parent)
  {
    // create the bridge
    this->bridge = new Bridge(this);

    // create a webkit browser
    this->view = new QWebView(this);
    this->connect(this->view, SIGNAL(loadFinished(bool)), this, SLOT(OnPageLoaded(bool)));
    this->connect(this->view->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(OnLoadJSObject()));

    // show the browser
    this->view->show();

    this->character = 0x0;
    this->gameSystem = 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CharacterForm::show(const QString fileName, QVariantMap *character, gsdl::GameSystem *gameSystem) {

    this->character = character;
    this->gameSystem = gameSystem;

    // load html content
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {
      QByteArray data = file.readAll();
      QString html(data);
      this->view->setHtml(html);
    }
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CharacterForm::resizeEvent(QResizeEvent *) {
    this->view->setGeometry(QRect(10,10,this->width()-20,this->height()-20));
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString CharacterForm::buildSimpleField(gsdl::Field *metaField, QWebElement &element, const QString fieldName) {
    QString clazz = element.attribute("class");
    clazz.append(clazz.isEmpty() ? "simple field" : " simple field");
    QString label = element.attribute("data-label").isEmpty() ? fieldName : element.attribute("data-label");


    QByteArray result;

    result.append("<label class=\"" + clazz + "\" >").append(label).append("</label>");
    result.append("<input type=\"text\" value=\"Calculate Me\" onChange=\"javascript:engine.fieldChanged('" + fieldName +  "');\" />");

    return QString(result);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CharacterForm::addField(QWebElement &element, const QString fieldName) {
    gsdl::Field *metaField = this->gameSystem->getField(fieldName);

    if(metaField != 0x0) {
      qDebug() << "ADD FIELD: " << fieldName << ", TYPE:" << metaField->getFieldType();
      element.appendInside(buildSimpleField(metaField,element,fieldName));
    } else {
      qDebug() << "FAILED TO FIND FIELD: " << fieldName;
    }
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CharacterForm::OnLoadJSObject() {
    this->view->page()->mainFrame()->addToJavaScriptWindowObject("engine",this->bridge);
    qDebug() << "BRIDGE ADDED";
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CharacterForm::OnPageLoaded(bool flag) {
    QWebFrame *frame = this->view->page()->mainFrame();
    QWebElement document = frame->documentElement();

    QWebElementCollection fields = document.findAll("div");
    foreach(QWebElement field, fields) {
      QString fieldName = field.attribute("data-field-name");
      if(!fieldName.isEmpty()) this->addField(field, fieldName);
    }



/*

    for(int i=fields.count()-1; i >=0; i--){

      QWebElement el = fields.at(i);




      QString data = el.attribute("name");
      QString name(data);
      name.replace(" ","_");
      QString clazz = el.attribute("class");
      QString html = "<div class=\"" + clazz+ "\"/><label>" + el.attribute("name") + "</label><input type=\"text\" name=\"" + name + "\" data-field-name=\"" + data + "\" class=\"" + clazz + "\" /></div>";

      el.appendInside(html);
    }
*/

  }

}
