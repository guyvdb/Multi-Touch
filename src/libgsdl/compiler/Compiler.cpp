#include "Compiler.h"

#include "gramma/Gramma.h"

#include <QDebug>

#include <iostream>
#include <fstream>


namespace gsdl {

  namespace internal {
    // global to this namespace
    GameSystem *gameSystem = 0x0;


    void createGameSystem(std::basic_string<char> value) {
      gameSystem = new GameSystem(QString::fromStdString(value));
      qDebug() << "CREATE GAME SYSTEM: NAME=" << gameSystem->getName();
    }

    void createRuleSource(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        RuleSource *source =  gameSystem->createRuleSource(QString::fromStdString(value));
        qDebug() << "CREATE RULE SOURCE: VALUE=" << source->getValue();
      }
    }

    void createGroup(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        Group *group= gameSystem->getCharacter()->createGroup(QString::fromStdString(value));
        qDebug() << "CREATE GROUP: NAME=" << group->getName();
      }
    }

    void createField(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(QString::fromStdString(value));
            qDebug() << "CREATE FIELD: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName();
          }
        }
      }
    }

    void createLookup(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            QString name = QString::fromStdString(value);
            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(name);
            field->setLookupTableName(name);
            qDebug() << "CREATE LOOKUP: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName() << ", TABLE=" << field->getLookupTableName();
          }
        }
      }
    }

    void createHalfMacro(std::basic_string<char> value) {
      qDebug() << "enter createHalfMacro";
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            QString target = QString::fromStdString(value);
            QString name = "Half " + target;

            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(name);
            field->setHalfMacroFieldName(target);
            qDebug() << "CREATE LOOKUP: NAME=" << QString::fromStdString(value) << " GROUP=" << field->getGroup()->getName() << ", TARGET=" << field->getHalfMacroFieldName();
          }
        }
      }
    }

    void createModifyMacro() {
      qDebug() << "enter createModifyMacro";

    }

    void createModifierMacro() {
      qDebug() << "enter createModifierMacro";

    }

    void createAddMacro() {
      qDebug() << "enter createAddMacro";

    }

    void createTable() {
      qDebug() << "enter createTable";

    }

    void createTableItem() {
      qDebug() << "enter createTableItem";

    }

    void createInformation() {
      qDebug() << "enter createInformation";

    }

    void createBaseValue() {
      qDebug() << "enter createBaseValue";

    }


    void setSystemName(std::basic_string<char> value) {
      qDebug() << "enter createRuleSource";

    }

    void setGroupName(std::basic_string<char> value) {
      qDebug() << "enter setSystemName";

    }

    void setName(std::basic_string<char> value) {
      qDebug() << "enter setName";

    }

    void setTableName(std::basic_string<char> value) {
      qDebug() << "enter setTableName";

    }

    void setForeignKey(std::basic_string<char> value) {
      qDebug() << "enter setForeignKey";

    }

    void setTableItemName(std::basic_string<char> value) {
      qDebug() << "enter setTableItemName";

    }

    void setTableItemValue(std::basic_string<char> value) {
      qDebug() << "enter setTableItemValue";

    }

    void setPairKey(std::basic_string<char> value) {
      qDebug() << "enter setPairKey";

    }

    void setPairValue(std::basic_string<char> value) {
      qDebug() << "enter setPairValue";

    }

  } // end internal namespace


  Compiler::Compiler(QObject *parent) : QObject(parent)
  {
  }

  GameSystem* Compiler::compile(const QString filename) {
    internal::gameSystem = 0x0;  // reset any reference to old game system

    // open a stream
    std::ifstream stream(filename.toAscii().constData());

    // declare our iterator types
    typedef std::istreambuf_iterator<char> base_iterator_type;
    base_iterator_type in_begin(stream);

    typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
    forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
    forward_iterator_type fwd_end;


    // declare our gramma
    typedef gsdl_gramma<forward_iterator_type> gsdl_p;
    gsdl_p g;

    // parse the file into our ast
    bool r = boost::spirit::qi::phrase_parse(fwd_begin, fwd_end, g, boost::spirit::ascii::space);

    QString msg = r ? "PARSE OK" : "SYNTAX ERROR";
    qDebug() << msg;

    return internal::gameSystem; // the calling function is responisable to free it.
  }

}
