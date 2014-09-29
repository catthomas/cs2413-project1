#ifndef __FIELD__H
#define __FIELD__H
/*
NAME: Catherine Thomas
DATE: 09/16/2014

The Field class is representative of a field inside a bibliographical data entry. It is
the parent class of TextField and NumberField.
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
	virtual int size();
};
//-----------------------------------
Field::Field()
{
	_designator = "";
} //end default constructor
Field::Field(String designator)
{
	_designator = designator;
} //end constructor with designator
Field::~Field()
{
	//Do nothing
} //end ~Field
String Field::designator()
{
	return _designator;
} //end getDesignator
void Field::setDesignator(String designator)
{
	_designator = designator;
} //end setDesignator
ostream& operator << (ostream& s, Field& f)
{
	f.display(s);
	return s;
} //end <<
void Field::display(ostream& s)
{
	s << _designator;
} //end display

#endif
