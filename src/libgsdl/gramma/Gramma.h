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
#ifndef GSDLGRAMMA_H
#define GSDLGRAMMA_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/qi_no_skip.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;


namespace gsdl {

  namespace internal {
    void createGameSystem(std::basic_string<char> value);
    void createRuleSource(std::basic_string<char> value);
    void createGroup(std::basic_string<char> value);
    void createField(std::basic_string<char> value);
    void createLookup(std::basic_string<char> value);
    void createHalfMacro(std::basic_string<char> value);
    void createModifierMacro(std::basic_string<char> value);
    void createAddMacro();
    void appendAddMacroFactor(std::basic_string<char> value);
    void createTable(std::basic_string<char> value);
    void setForeignKey(std::basic_string<char> value);
    void createTableItem(std::basic_string<char> value);
    void createInformation(std::basic_string<char> value);

    void setListCharacterByFieldName(std::basic_string<char> value);
    //-----------------------------------------------

    void createModifyMacro();
    void createBaseValue();

    void setSystemName(std::basic_string<char> value);
    void setGroupName(std::basic_string<char> value);
    void setName(std::basic_string<char> value); //change to setFieldName()
    void setTableName(std::basic_string<char> value);

    void setTableItemName(std::basic_string<char> value);
    void setTableItemValue(std::basic_string<char> value);
    void setPairKey(std::basic_string<char> value);
    void setPairValue(std::basic_string<char> value);

  } // end internal namespace


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  template <typename Iterator>
  struct gsdl_gramma : qi::grammar<Iterator,ascii::space_type >
  {

    qi::rule<Iterator, std::string(), ascii::space_type > variable;
    qi::rule<Iterator> preserve_eol;

    // containers
    qi::rule<Iterator, ascii::space_type > system;
    qi::rule<Iterator, ascii::space_type > rule_sources;
    qi::rule<Iterator, ascii::space_type > rule_source;
    //qi::rule<Iterator, ascii::space_type > hooks;
    qi::rule<Iterator, ascii::space_type > character;
    qi::rule<Iterator, ascii::space_type > group;
    qi::rule<Iterator, ascii::space_type > groups;
    qi::rule<Iterator, ascii::space_type > tables;
    qi::rule<Iterator, ascii::space_type > table;

    // list_by
    qi::rule<Iterator, ascii::space_type > list_by;

    // gui items
    //qi::rule<Iterator, ascii::space_type > hook_item;
    //qi::rule<Iterator, ascii::space_type > hook_items;
    //qi::rule<Iterator, ascii::space_type > list_character_by;

    // macros
    qi::rule<Iterator, ascii::space_type > half_macro;        // create half of a field (rounding down)
    qi::rule<Iterator, ascii::space_type > modifier_macro;    // lookup a modifier value from a modifier table
    qi::rule<Iterator, ascii::space_type > add_macro;         // add two fields together
    qi::rule<Iterator, ascii::space_type > increment_macro;   // increment the value of a field

    // tables
    qi::rule<Iterator, ascii::space_type > fk;
    qi::rule<Iterator, ascii::space_type > item;
    qi::rule<Iterator, ascii::space_type > table_entry;
    qi::rule<Iterator, ascii::space_type > table_entries;
    qi::rule<Iterator, ascii::space_type > item_entry;
    qi::rule<Iterator, ascii::space_type > item_entries;

    // item modifiers
    qi::rule<Iterator, ascii::space_type > item_value;
    qi::rule<Iterator, ascii::space_type > modify_value;
    qi::rule<Iterator, ascii::space_type > base_value;

    // info
    qi::rule<Iterator, ascii::space_type > information;

    // fields
    qi::rule<Iterator, ascii::space_type > field;
    qi::rule<Iterator, ascii::space_type > lookup;
    qi::rule<Iterator, ascii::space_type > field_type;
    qi::rule<Iterator, ascii::space_type > fields;


    gsdl_gramma() : gsdl_gramma::base_type(system)
    {
      using qi::int_;
      using qi::lit;
      using qi::double_;
      using qi::lexeme;
      using ascii::char_;
      using qi::no_skip;
      using qi::eol;

      variable %= lexeme['"' >> +(char_ - '"') >> '"'];

      system %=
          lit("system")
          >> variable[&internal::createGameSystem]
          >> '{'
          >>      rule_sources
          >>      character
          >>      tables
         // >>      hooks
          >> '}'
          ;

      rule_sources %=
          lit("sources")
          >> '{'
          >> *rule_source
          >> '}'
          ;

      rule_source %=
          lit("source")
          >> variable[&internal::createRuleSource]
          //>> eol
          ;
/*
      hooks %=
          lit("hooks")
          >> '{'
          >> hook_items
          >> '}'
          ;

      hook_items %=
          *hook_item;

      hook_item %=
          (list_character_by)
          ;

      list_character_by %=
          lit("list_character_by")
          >> variable[&internal::setListCharacterByFieldName]
          ;
          */

      character %=
          lit("character")
          >> '{'
          >>    list_by
          >>    groups
          >> '}'
          ;

      list_by %=
          lit("list_by")
          >> variable[&internal::setListCharacterByFieldName]
          ;

      group %=
          lit("group")
          >> variable[&internal::createGroup]
          >> '{'
          >>     fields
          >> '}'
          ;

      groups %=
          *group
          ;

      field_type %=
          (field | lookup | half_macro | modifier_macro | add_macro)
          ;

      fields %=
          *field_type
          ;

      field %=
          lit("field")
          >> variable[&internal::createField]
          ;

      lookup %=
          lit("lookup")
          >> variable[&internal::createLookup]
          ;


      half_macro %=
          lit("half")
          >> variable[&internal::createHalfMacro]
          ;

      modifier_macro %=
          lit("modifier")
          >> variable[&internal::createModifierMacro]
          ;

      add_macro %=
          lit("add")[&internal::createAddMacro]
          >> variable[&internal::appendAddMacroFactor]
          >> lit("+")
          >> variable[&internal::appendAddMacroFactor]
          ;

      tables %=
          lit("tables")
          >> '{'
          >> *table
          >> '}'
          ;

      table %=
          lit("table")
          >> variable[&internal::createTable]
          >> '{'
          >>    table_entries
          >> '}'
          ;

      fk %=
          lit("auto")
          >> variable[&internal::setForeignKey]
          ;

      table_entry %=
          (fk | item)
          ;

      table_entries %=
          *table_entry
          ;

      item %=
          lit("item")
          >> variable[&internal::createTableItem]
          >> '{'
          >>    item_entries
          >> '}'
          ;

      item_value %=
          lit("value")
          >> variable[&internal::setTableItemValue]
          ;

      information %=
          lit("info")
          >> variable[&internal::createInformation]
          ;

      modify_value %=
          lit("modify")
          >> variable[&internal::setPairKey]
          >> variable[&internal::setPairValue]
          ;

      base_value %=
          lit("base")[&internal::createBaseValue]
          >> variable[&internal::setPairKey]
          >> variable[&internal::setPairValue]
          ;

      increment_macro %=
          lit("increment")
          >> variable
          >> variable
          ;

      item_entry %=
          (item_value | information | modify_value | base_value | increment_macro)
          ;

      item_entries %=
          *item_entry
          ;


    }

  };

}
#endif // GSDLGRAMMA_H
