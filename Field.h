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
using namespace std;

class Field{
	friend ostream& operator << (ostream& s, Field& f);
private:
	string _designator; //name of field
public:
	Field();
	Field(string designator);
	virtual ~Field();
	string getDesignator();
	void setDesignator(string designator);
	virtual void display(ostream& s);
	int size();
};

Field::Field()
{
	_designator = "";
} //end Field
Field::Field(string designator)
{
	_designator = designator;
} //end Field
Field::~Field()
{

} //end ~Field
string Field::getDesignator()
{
	return _designator;
} //end getDesignator
void Field::setDesignator(string designator)
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


template <class DataType>
class AbstractArrayClass
{

public:
	virtual int size() const = NULL;
	virtual DataType& operator[] (int k) = NULL;
};
