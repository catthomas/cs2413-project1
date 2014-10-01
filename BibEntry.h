#ifndef __BIBENTRY__H
#define __BIBENTRY__H

#include <iostream>
#include "ArrayClass.h"
#include "String.h"
#include "TextField.h"

//-----------------------------------------BibEntry Classs --------------------------------//
/*
NAME: Catherine Thomas
DATE: 09/16/2014

The Bibentry class stores data on a specific bibliographic entry. It tracks the longest field,
designator of the longest field, number of fields, and number of authors.
Each bibentry has a type (i.e. article, journal), a name, and a list of fields which each have
a field designator and value.
*/
class BibEntry {
	friend ostream& operator << (ostream &s, BibEntry &be);
private:
	String _type; //Represents the type of the bibentry
	String _name; //Represents the name of the bibentry
	ArrayClass<TextField> _fields; //Holds the fields for the bibentry
	int _numberOfFields; //Tracks the number of fields in the bibentry
	int _numberOfAuthors; //Tracks the number of authors in the bibentry
	String _longestFieldDesignator; //Tracks the name of the longest field
	int _longestFieldLength; //Tracks the length of the longest field
public:
	BibEntry();
	BibEntry(String type, String name);
	virtual ~BibEntry();
	String type();
	String name();
	int numberOfAuthors();
	String longestFieldDesignator();
	int longestFieldLength();
	int numberOfFields();
	void setName(String name);
	void setType(String type);
	void setNumberOfFields(int numberFields);
	void setNumberOfAuthors(int numberAuthors);
	void setLongestFieldDesignator(String longestField);
	void setLongestFieldLength(int longFieldLength);
	void addField(TextField field);
	void display(ostream& s);
};
/*
This is the default constructor for a bib entry.
*/
BibEntry::BibEntry()
{
	_type = "";
	_name = "";
	_fields = ArrayClass<TextField>(20); //No more than 20 fields in the bib entry
	_numberOfFields = 0;
	_numberOfAuthors = 0;
	_longestFieldDesignator = "";
	_longestFieldLength = 0;
} //end BibEntry default constructor
//------------------------------------------
/*
This constructor takes in a type (i.e. 'journal', article') for the 
bib entry as well as a name. Both pararmeters are strings.
*/
BibEntry::BibEntry(String type, String name)
{
	_type = type;
	_name = name;
	_fields = ArrayClass<TextField>(20); //No more than 20 fields in the bib entry
	_numberOfFields = 0;
	_numberOfAuthors = 0;
	_longestFieldDesignator = "";
	_longestFieldLength = 0;
} //end BibEntry constructor with type and name
//-----------------------------------------
BibEntry::~BibEntry()
{
} // end BibEntry
//---------------------------------------------
/*
Returns the type of the bib entry (i.e. 'journal' or 'article') 
as a String.
*/
String BibEntry::type()
{
	return _type;
} //end type
//--------------------------------------------
/*
Returns the name of the bib entry as a a String.
*/
String BibEntry::name()
{
	return _name;
} //end name
//--------------------------------------------
/*
Returns the number of fields of the bib entry
as an int.
*/
int BibEntry::numberOfFields(){
	return _numberOfFields;
} //end getNumberOfFields
//--------------------------------------------
/*
Returns the number of authors in a bib entry.
*/
int BibEntry::numberOfAuthors(){
	return _numberOfAuthors;
} //end getNumberOfAuthors
//-------------------------------------------
/*
Returns the designator of the longest field 
in a bib entry.
*/
String BibEntry::longestFieldDesignator(){
	return _longestFieldDesignator;
} //end getLongestFieldDesignator
//-------------------------------------------
/*
Returns the length of the longest field in a bib entry.
*/
int BibEntry::longestFieldLength(){
	return _longestFieldLength;
} //end longestFieldLength
//--------------------------------------------
/*
Mutator the name of a bib entry.
*/
void BibEntry::setName(String name)
{
	_name = name;
} //end setName
//-------------------------------------------
/*
Mutator for the type of a bib entry.
*/
void BibEntry::setType(String type)
{
	_type = type;
} //end setType
//---------------------------------------------
/*
Mutator for the number of fields in a bib entry.
*/
void BibEntry::setNumberOfFields(int numberFields){
	_numberOfFields = numberFields;
} //end setNumberOfFields
//-------------------------------------------------
/*
Mutator for the number of authors in a bib entry.
*/
void BibEntry::setNumberOfAuthors(int numberAuthors){
	_numberOfAuthors = numberAuthors;
} //end setNumberOfAuthors
//---------------------------------------------------
/*
Mutator for the longest field designator in a bib entry.
*/
void BibEntry::setLongestFieldDesignator(String longestField){
	_longestFieldDesignator = longestField;
} //end setLongestFieldDesignator
//---------------------------------------------------
/*
Mutator for the longest field length in a bib entry.
*/
void BibEntry::setLongestFieldLength(int longFieldLength){
	_longestFieldLength = longFieldLength;
}//end setLongestFieldLength
//--------------------------------------------------
/*
This method adds a new field to a bib entry.
It has one parameter named 'field' which is a TextField
which representst the new field.
*/
void BibEntry::addField(TextField field)
{
	//Check if field is now longest
	if (field.length() > _longestFieldLength){
		_longestFieldLength = field.length();
		_longestFieldDesignator = field.designator();
	}

	_fields[_numberOfFields] = field;
	++_numberOfFields;
} //end addField
//-------------------------------------------------
/*
This is the overloaded ostream operator for a bib entry.
*/
ostream& operator << (ostream& s, BibEntry& be)
{
	be.display(s);
	return s;
} //end <<
//----------------------------------------------------
void BibEntry::display(ostream& s)
{	
	// << counts = { fields: 11; authors: 3; longest field : url; length: 62 };
	//Format first line
	s << "@" << _type << "{" << _name << "," << endl;

	//Format fields
	for (int i = 0; i < _numberOfFields; ++i){
		s << "	" << _fields[i] << endl;
	}

	//Output counts
	s << "	counts = {fields: " << _numberOfFields << "; authors:" << _numberOfAuthors << "; longest field: "
		<< _longestFieldDesignator << "; length: " << _longestFieldLength << "}" << endl;

	 //ending bracket
	 s << "}" << endl;
} //end display
#endif