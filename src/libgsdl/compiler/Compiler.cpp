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
    }

    void createRuleSource(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        gameSystem->addRuleSource(QString::fromStdString(value));
      }
    }

    void createGroup(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        gameSystem->getCharacter()->createGroup(QString::fromStdString(value));
      }
    }

    void createField(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
            gameSystem->getCharacter()->getCurrentGroup()->createField(QString::fromStdString(value));
          }
        }
      }
    }

    void createLookup(std::basic_string<char> value) {
      if(gameSystem != 0x0) {
        if(gameSystem->getCharacter() != 0x0) {
          if(gameSystem->getCharacter()->getCurrentGroup() != 0x0 ) {
           Field *field = gameSystem->getCharacter()->getCurrentGroup()->createField(QString::fromStdString(value));
           field->setLookupTableName(field->getName());
          }
        }
      }
    }

    void createHalfMacro() {

    }

    void createModifyMacro() {

    }

    void createModifierMacro() {

    }

    void createAddMacro() {

    }

    void createTable() {

    }

    void createTableItem() {

    }

    void createInformation() {

    }

    void createBaseValue() {

    }


    void setSystemName(std::basic_string<char> value) {

    }

    void setGroupName(std::basic_string<char> value) {

    }

    void setName(std::basic_string<char> value) {

    }

    void setTableName(std::basic_string<char> value) {

    }

    void setForeignKey(std::basic_string<char> value) {

    }

    void setTableItemName(std::basic_string<char> value) {

    }

    void setTableItemValue(std::basic_string<char> value) {

    }

    void setPairKey(std::basic_string<char> value) {

    }

    void setPairValue(std::basic_string<char> value) {

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
