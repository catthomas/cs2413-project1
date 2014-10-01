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
/*
This is the default constructor for an author.
It sets the author's name to the empty String.
*/
Author::Author(){
	_name = "";
} //end Author
//----------------------------------------
/*
This is a constructor for an Author which takes
one parameter: a String representing the name of the 
author.
*/
Author::Author(String name){
	_name = name;
} //end Author
//-------------------------------------
/*
Destructor for an Author object.
*/
Author::~Author(){
} //end ~Author
//----------------------------------
/*
Accessor method for the name of an Author
*/
String Author::name(){
	return _name;
}//end getName
//--------------------------------
/*
Mutator method for the name of an author.
*/
void Author::setName(String name){
	_name = name;
} //end setName
//------------------------------------
/*
Overload ostream operator for an Author.
*/
ostream& operator << (ostream& s, Author& af)
{
	af.display(s);
	return s;
} //end <<
//--------------------------------------
/*
Displays the author.
*/
void Author::display(ostream& s)
{
	s << _name;
} //end display

#endif