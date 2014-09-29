#ifndef __STRING__H
#define __STRING__H
#include "ArrayClass.h"

/*
This is a custom-written string class.
The code for this class was taken from the book:
"Data Structures Featuring C++" written by Dr. Sridhar
Radhakrishnan from the University of Oklahoma.
*/

class StringSizeException : public ArrayException { };
class String : virtual public ArrayClass < char >
{
	friend ostream& operator<< (ostream& s, const String& str);
public:
	String();
	String(int n);
	String(const String& str);
	String(char* s);
	virtual ~String();
	void operator= (const String& str);
	virtual int length() const;
	virtual int size() const;
	bool operator== (const String& str) const;
	bool operator< (const String& str) const;
	bool operator> (const String& str) const;
	void concatenate(const String& str);
	int index(char c, int start) const;
	int index(char c) const;
	int lastIndex(char c, int start) const;
	int lastIndex(char c) const;
	String substring(int left, int len) const;
	String operator+ (const String& str);
	bool equalsIgnoreCase(const String& str);
};

String::String() : ArrayClass<char>(1, '\0')
{
	//Do nothing - super class initializes
} //end default constructor
//---------------------------------------------------
String::String(int n) : ArrayClass<char>(n + 1, '\0')
{
	//Do nothing - super class initializes
} //end constructor with n
//--------------------------------------------------
String::String(char* s) : ArrayClass<char>(strlen(s) + 1)
{
	strcpy(paObject, s);
} //end constructor with literal string
//-------------------------------------------------
String::String(const String& str) : ArrayClass<char>(str)
{
	//Do nothing - super class copy constructor called
} //end copy constructor
//-------------------------------------------------
String::~String()
{
	//Do nothing
} //end destructor
//-------------------------------------------------
void String::operator= (const String& str)
{
	if (size() == 0) //constructed by default
	{
		ArrayClass<char>::operator= (str); //call parent operator
		return;
	}
	//NOTE: length = # of elements
	int max = str.length(); //not constructed by default
	bool overflow = false;
	if (_size - 1 < max)
	{
		overflow = true;
		max = size();
	}
	strncpy(paObject, str.paObject, max);
	paObject[max] = '\0'; //null terminated
	if (overflow) throw StringSizeException(); //String passed is larger than could be accomodated
} //end overloaded =
//---------------------------------------------------
int String::size() const //here size is equivalent to capacity
{
	return ArrayClass<char>::size() - 1; //needs room for the terminating null
} //end size
//-------------------------------------------------
int String::length() const
{
	return strlen(paObject);
} //end length
//-------------------------------------------------
bool String::operator== (const String& str) const
{
	return (strcmp(paObject, str.paObject) == 0); //strcmp returns 0 when equal
} //end overloaded ==
//------------------------------------------------
bool String::operator< (const String& str) const
{
	return (strcmp(paObject, str.paObject) < 0);
} //end overloaded <
//------------------------------------------------
bool String::operator> (const String& str) const
{
	return (strcmp(paObject, str.paObject) > 0);
} //end overloaded >
//TODO: another comparison??
//-----------------------------------------------
bool String::equalsIgnoreCase(const String& str)
{
	return (_stricmp(paObject, str.paObject)); //compares strings without sensitivity
} //end equalsIgnoreCase
//-------------------------------------------------
void String::concatenate(const String& str)
{
	int len = length(); //store length() for efficiency's sake
	int max = str.length();
	bool overflow = false;
	if (size() < max + len)
	{
		overflow = true;
		max = size() - len;
	}
	strncpy(paObject + len, str.paObject, max);
	paObject[max + len] = '\0'; //null terminate
	if (overflow) throw StringSizeException(); //String passed is larger than could be accomodated
} //end concatenate
//--------------------------------------------------
String String::operator+ (const String& str)
{
	String temp(length() + str.length());
	temp = (*this);
	temp.concatenate(str);
	return temp;
} //end overloaded +
//---------------------------------------------------
int String::index(char c, int start) const
{
	//if start is past the end, obviously c isn't present
	if (start >= length()) return -1;
	char* pc = strchr(paObject + start, c);
	if (pc == NULL) return -1;
	return (pc - paObject);
} //end index
//------------------------------------------------------
int String::index(char c) const
{
	return index(c, 0);
} //end overloaded index
//---------------------------------------------------
int String::lastIndex(char c, int start) const
{
	//if start is past the end, obviously c isn't present
	if (start >= length()) return -1;
	char* pc = strrchr(paObject + start, c); //strrchr = last character
	if (pc == NULL) return -1;
	return (pc - paObject);
} //end lastIndex
//------------------------------------------------------
int String::lastIndex(char c) const
{
	return lastIndex(c, 0);
} //end overloaded lastIndex
//------------------------------------------------------
String String::substring(int left, int len) const
{
	//a negative index is illegal
	if (left < 0) throw ArrayBoundsException();
	//no need to throw exception if left is at least
	//legal, if not actually in bounds
	String sub(len);
	if (left > length()) return sub;
	int max = len;
	if (max + left > length()) max = length() - left;
	strncpy(sub.paObject, &paObject[left], max);
	sub.paObject[max] = '\0'; //always null terminate!!
	return sub;
} //end substring
//--------------------------------------------------------
ostream& operator<< (ostream& s, const String& str)
{
	s << str.paObject;
	return s;
} //end <<
#endif