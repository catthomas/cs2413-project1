#ifndef __ABSTRACTVECTOR__H
#define __ABSTRACTVECTOR__H

#import "AbstractArray.h"

/*
This is the abstract class for a Vector.
The code for this class was taken from the book:
"Data Structures Featuring C++" written by Dr. Sridhar
Radhakrishnan from the University of Oklahoma.

It is a parent class to Vector.h
*/

template <class DataType>
class AbstractVector : virtual public AbstractArrayClass<DataType>
{
public:
	//insert a new object at position index of the vector
	virtual void insert(const DataType& item, int index) = NULL;
	//remove the object at position index of the vector
	virtual void remove(int index) = NULL;
	//adds item at the end of the Vector
	virtual void add(const DataType& item) = NULL;
};

#endif