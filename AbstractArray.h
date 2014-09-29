#ifndef __ABSTRACTARRAY__H
#define __ABSTRACTARRAY__H

#include <iostream>
using namespace std;
#include "Exception.h"
class ArrayException : public Exception { };
class ArrayMemoryException : public ArrayException { }; //Array does not fit into available memory
class ArrayBoundsException : public ArrayException { }; //Tried to access element outside of range of array

/*
This is the abstract base class for the ArrayClass.
The code for this class was taken from the book:
"Data Structures Featuring C++" written by Dr. Sridhar
Radhakrishnan from the University of Oklahoma.

It is the parent class to ArrayClass.s
*/
template <class DataType>
class AbstractArrayClass
{
public: 
	virutal int size() const = NULL;
	virtual DataType& operator[] (int k) = NULL;
};

template <class DataType>
ostream& operator << <DataType>(ostream& s,
	AbstractArrayClass<DataType>& ac)
{
	s << "[";
	for (int i = 0; i < ac.size(); i++)
	{
		if (i > 0)
		{
			s << ',';
		}
		s << ac[i];
	}
	s << "]";
	return s;
} //end overloaded <<
#endif