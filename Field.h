#ifndef __FIELD__H
#define __FIELD__H
/*
NAME: Catherine Thomas
DATE: 09/16/2014

The Field class is representative of a field inside a bibliographical data entry. It is
the parent class of TextField.
*/

#include <iostream>
#include <cstring>
#include "String.h"
using namespace std;

class Field{
	friend ostream& operator << (ostream& s, Field& f);
private:
	String _designator; //name of field
public:
	Field();
	Field(String designator);
	virtual ~Field();
	String designator();
	void setDesignator(String designator);
	virtual void display(ostream& s);
	int length();
};
//-----------------------------------
/*
Default constructor for a field object.
Set the designator of the field to be empty.
*/
Field::Field()
{
	_designator = "";
} //end default constructor
//-------------------------------------
/*
Constructor for a Field object which 
takes one parameter: String representing the designator.
*/
Field::Field(String designator)
{
	_designator = designator;
} //end constructor with designator
//--------------------------------
/*
Destructor for a field object.
*/
Field::~Field()
{
	//Do nothing
} //end ~Field
//---------------------------------
/*
Accessor for the designator of a field.
*/
String Field::designator()
{
	return _designator;
} //end getDesignator
//----------------------------------
/*
Mutator for the designator of a field.
*/
void Field::setDesignator(String designator)
{
	_designator = designator;
} //end setDesignator
//------------------------------------
/*
Overloaded ostream operator for a Field object.
*/
ostream& operator << (ostream& s, Field& f)
{
	f.display(s);
	return s;
} //end <<
//--------------------------------------
/*
Displays the designator of a field.
*/
void Field::display(ostream& s)
{
	s << _designator;
} //end display

#endif
