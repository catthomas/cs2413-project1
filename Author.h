#ifndef __AUTHOR__H
#define __AUTHOR__H

#include "String.h"
//-------------------------------------Author Class--------------------------------//
/*
NAME: Catherine Thomas
DATE: 09/16/2014

The Author class is representative of an author in a bibliographical data entry.
*/
class Author {
	friend ostream& operator << (ostream &s, Author &af);
private:
	String _name; //name of the author
public:
	Author();
	Author(String name);
	virtual ~Author();
	String name();
	void setName(String name);
	void display(ostream& s);
};

Author::Author(){
	_name = "";
} //end Author
Author::Author(String name){
	_name = name;
} //end Author
Author::~Author(){

} //end ~Author
String Author::name(){
	return _name;
}//end getName
void Author::setName(String name){
	_name = name;
} //end setName
ostream& operator << (ostream& s, Author& af)
{
	af.display(s);
	return s;
} //end <<
void Author::display(ostream& s)
{
	s << _name;
} //end display

#endif