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

    //-----------------------------------------------



    void createHalfMacro();
    void createModifyMacro();
    void createModifierMacro();
    void createAddMacro();
    void createTable();
    void createTableItem();
    void createInformation();
    void createBaseValue();



    void setSystemName(std::basic_string<char> value);
    void setGroupName(std::basic_string<char> value);
    void setName(std::basic_string<char> value); //change to setFieldName()
    void setTableName(std::basic_string<char> value);
    void setForeignKey(std::basic_string<char> value);
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
    qi::rule<Iterator, ascii::space_type > source_data;
    qi::rule<Iterator, ascii::space_type > character;
    qi::rule<Iterator, ascii::space_type > group;
    qi::rule<Iterator, ascii::space_type > groups;
    qi::rule<Iterator, ascii::space_type > table;

    // macros
    qi::rule<Iterator, ascii::space_type > half_macro;        // create half of a field (rounding down)
    qi::rule<Iterator, ascii::space_type > modifier_macro;    // lookup a modifier value from a modifier table
    qi::rule<Iterator, ascii::space_type > add_macro;         // add two fields together


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
          >>      *(source_data)
          >>      character
          >>      *(table)
          >> '}'
          ;

      source_data %=
          lit("source")
          >> variable[&internal::createRuleSource]
          //>> eol
          ;

      character %=
          lit("character")
          >> '{'
          >>    groups
          >> '}'
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
          lit("half")[&internal::createHalfMacro]
          >> variable[&internal::setName]
          ;

      modifier_macro %=
          lit("modifier")[&internal::createModifierMacro]
          >> variable[&internal::setName]
          ;

      add_macro %=
          lit("add")[&internal::createAddMacro]
          >> variable[&internal::setName]
          >> lit("plus")
          >> variable[&internal::setName]
          ;


      table %=
          lit("table")[&internal::createTable]
          >> variable[&internal::setTableName]
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
          lit("item")[&internal::createTableItem]
          >> variable[&internal::setTableItemName]
          >> '{'
          >>    item_entries
          >> '}'
          ;

      item_value %=
          lit("value")
          >> variable[&internal::setTableItemValue]
          ;

      information %=
          lit("info")[&internal::createInformation]
          >> variable[&internal::setPairKey]
          >> variable[&internal::setPairValue]
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

      item_entry %=
          (item_value | information | modify_value | base_value)
          ;

      item_entries %=
          *item_entry
          ;
    }

  };

}
#endif // GSDLGRAMMA_H
