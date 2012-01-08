#include "GSDLCompiler.h"

#include "gramma/GSDLGramma.h"


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

    void createLookup() {
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

  }


  GSDLCompiler::GSDLCompiler(QObject *parent) : QObject(parent)
  {
  }

  GameSystem* GSDLCompiler::compile(const QString filename) {

  }

}
