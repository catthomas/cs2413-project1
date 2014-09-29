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
	String getValue();
	void setValue(String value);
	int size();
	void display(ostream& s);
}; //end TextField class

TextField::TextField()
{
	_value = NULL;
} //end TextField
TextField::TextField(String designator, String value) : Field(designator)
{
	_value = value;
} //end TextField
TextField::~TextField()
{
	//Do nothing
} //end ~TextField
String TextField::getValue()
{
	return _value;
}//end getalue
void TextField::setValue(String value)
{
	_value = value;
} //end setValue
int TextField::size()
{
	return _value.size();
} //end size
ostream& operator << (ostream& s, TextField& tf)
{
	tf.display(s);
	return s;
} //end <<
void TextField::display(ostream& s)
{
	s << getDesignator() << " = {" << _value << "},";
} //end display

#endif