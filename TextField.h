#ifndef __TEXTFIELD__H
#define __TEXTFIELD__H

#include "String.h"
#include "Field.h"

//-----------------------------------------TextField Class---------------------------------//
/*
NAME: Catherine Thomas
DATE: 09/16/2014

The TextField class is representative of a field in a bibliographic data entry that
should be kept as a string value. Examples of this include url or journal. It is a
subclass of Field.
*/
class TextField : public Field{
	friend ostream& operator << (ostream &s, TextField &tf);
private:
	String _value;
public:
	TextField();
	TextField(String designator, String value);
	virtual ~TextField();
	String value();
	void setValue(String value);
	int length();
	void display(ostream& s);
}; //end TextField class
//----------------------------------
/*
Default constructor for a TextField.
Sets the field's value to the empty string.
*/
TextField::TextField()
{
	_value = "";
} //end TextField
//----------------------------------
/*
Constructor with parameters for a TextField.
Takes in two String values: one representing
the designator, and the other the value.
*/
TextField::TextField(String designator, String value) : Field(designator)
{
	_value = value;
} //end TextField
//----------------------------------
/*
Destructor for a TextField
*/
TextField::~TextField()
{
	//Do nothing
} //end ~TextField
//--------------------------------
/*
Accessor for the value of a TextField
*/
String TextField::value()
{
	return _value;
}//end getalue
//--------------------------------
/*
Mutator for the value of a TextField
*/
void TextField::setValue(String value)
{
	_value = value;
} //end setValue
//-----------------------------
/*
Returns the length of the value of TextField.
*/
int TextField::length()
{
	return _value.length();
} //end size
//------------------------------
/*
Overloaded ostream operator for a TextField
*/
ostream& operator << (ostream& s, TextField& tf)
{
	tf.display(s);
	return s;
} //end <<
//--------------------------------------
/*
Displays a TextField.s
*/
void TextField::display(ostream& s)
{
	s << designator() << " = {" << _value << "},";
} //end display

#endif