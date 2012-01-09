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

    void setListCharacterByFieldName(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        QString k = "LIST_CHARACTER_BY_FIELD_NAME";
        QString v = QString::fromStdString(value);
        gameSystem->addGuiMapping(k,v);
        qDebug() << "ADD GUI MAPPING: " << k << "=" << v;
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
            QString table(name);
            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(name);
            field->setLookupTableName(table);
            qDebug() << "CREATE LOOKUP: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName() << ", TABLE=" << field->getLookupTableName();
          }
        }
      }
    }

    void createHalfMacro(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            QString target = QString::fromStdString(value);
            QString name = "Half ";
            name.append(target);

            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(name);
            field->setHalfMacroFieldName(target);
            qDebug() << "CREATE HALF MACRO: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName() << ", TARGET=" << field->getHalfMacroFieldName();
          }
        }
      }
    }

    void createModifyMacro(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            QString target = QString::fromStdString(value);
            QString name("Half " + target);
            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(name);
            field->setHalfMacroFieldName(target);
            qDebug() << "CREATE HALF MACRO: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName() << ", TARGET=" << field->getHalfMacroFieldName();
          }
        }
      }
    }

    void createModifierMacro(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            QString target = QString::fromStdString(value);
            QString group = gameSystem->getCharacter()->getCurrentGroup()->getName();
            QString name (target + " " + group + " Modifier");
            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(name);
            field->setModifierMacroFieldName(target);
            field->setModifierTableName(group);
            qDebug() << "CREATE MODIFIER MACRO: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName() << ", TARGET=" << field->geModifierMacroFieldName() + ", TABLE=" << field->getModifierTableName();
          }
        }
      }
    }

    void createAddMacro() {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField("");
            qDebug() << "CREATE ADD MACRO: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName();
          }
        }
      }
    }


    void appendAddMacroFactor(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            if(gameSystem->getCharacter()->getCurrentGroup()->getCurrentField() != 0x0) {
              Field *field = gameSystem->getCharacter()->getCurrentGroup()->getCurrentField();
              field->appendAddMacroFactor(QString::fromStdString(value));
              qDebug() << "MODIFY ADD MACRO: NAME=" << field->getName() << " GROUP=" << field->getGroup()->getName();
            }
          }
        }
      }
    }

    void createTable(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        Table* table = gameSystem->createTable(QString::fromStdString(value));
        qDebug() << "CREATE TABLE: NAME=" << table->getName();
      }
    }

    void setForeignKey(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCurrentTable() != 0x0) {
          Table *table = gameSystem->getCurrentTable();
          table->setForeignKeyFieldName(QString::fromStdString(value));
          qDebug() << "SET FOREIGN KEY: TABLE=" << table->getName() << " KEY=" << table->getForeignKeyFieldName();
        }
      }
    }


    void createTableItem(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCurrentTable() != 0x0) {
          Item *item = gameSystem->getCurrentTable()->createItem(QString::fromStdString(value));
          qDebug() << "CREATE TABLE ITEM: NAME=" << item->getName() << ", VALUE=" << item->getValue();
        }
      }
    }

    void setTableItemValue(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCurrentTable() != 0x0) {
          if(gameSystem->getCurrentTable()->getCurrentItem() != 0x0) {
            Item *item = gameSystem->getCurrentTable()->getCurrentItem();
            item->setValue(QString::fromStdString(value));
            qDebug() << "MODIFY TABLE ITEM VALUE: NAME=" << item->getName() << ", VALUE=" << item->getValue();
          }
        }
      }
    }

    void createInformation(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCurrentTable() != 0x0) {
          if(gameSystem->getCurrentTable()->getCurrentItem() != 0x0) {
            Item *item = gameSystem->getCurrentTable()->getCurrentItem();
            item->addInfo(QString::fromStdString(value));
            qDebug() << "ADDED INFO: NAME=" << item->getName() << ", INFO=" << QString::fromStdString(value);
          }
        }
      }
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



    void setTableItemName(std::basic_string<char> value) {
      qDebug() << "enter setTableItemName";

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
