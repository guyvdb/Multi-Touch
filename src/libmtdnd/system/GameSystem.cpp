#include "GameSystem.h"
#include <QFile>
#include <QtScript>
#include <QDebug>



namespace mtdnd {

  GameSystem::GameSystem(QObject *parent) :  QObject(parent)
  {
    this->interpreter = new QScriptEngine(this);
  }

  bool GameSystem::load(const QString fileName) {
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {


      QVariantMap map;
      map.insert("name","joe");


      QScriptValue v = this->interpreter->toScriptValue(map);
      QScriptValue global = this->interpreter->globalObject();


      global.setProperty("Properties",v);

      QScriptValue main =  this->interpreter->evaluate("(" + file.readAll() + ")",fileName);

      QScriptValue x = v.property("x");
      qDebug() << x.toString();
      qDebug() << x.call().toString();

      //qDebug() << main.property("foo").toInteger();
      //qDebug() << main.toString();



      file.close();
    } else {
      return false;
    }
  }



}
