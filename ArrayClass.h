#ifndef __ARRAYCLASS__H
#define __ARRAYCLASS__H

#include "AbstractArray.h"

/*
This is a generic template for an Array Class
The code for this class was taken from the book:
"Data Structures Featuring C++" written by Dr. Sridhar
Radhakrishnan from the University of Oklahoma.

It is the parent class to Vector.h
*/

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

template <class DataType>
class ArrayClass : virtual public AbstractArrayClass < DataType >
{
protected:
	DataType* paObject; //pointer to the array
	int _size; //size of the array (i.e. capacity)
	void copy(const ArrayClass<DataType>& ac);
public:
	ArrayClass();
	ArrayClass(int n);
	ArrayClass(int n, const DataType& val);
	ArrayClass(const ArrayClass<DataType>& ac);
	virtual ~ArrayClass();
	virtual int size() const;
	virtual DataType& operator[] (int k);
	void operator= (const ArrayClass<DataType>& ac);
};

template <class DataType>
ArrayClass<DataType>::ArrayClass()
{
	_size = 0; //default in case allocation fails
	paObject = new DataType[ARRAY_CLASS_DEFAULT_SIZE];
	if (paObject == NULL) throw ArrayMemoryException(); //Array does not fit into available memorys
	_size = ARRAY_CLASS_DEFAULT_SIZE;
} //end default ArrayClass constructor

template <class DataType>
ArrayClass<DataType>::ArrayClass(int n)
{
	_size = 0; //default in case allocation fails
	paObject = new DataType[n];
	if (paObject == NULL) throw ArrayMemoryException(); //Array does not fit into available memory
	_size = n;
} //end ArrayClass constructor with n

template <class DataType>
ArrayClass<DataType>::~ArrayClass()
{
	if (paObject != NULL) delete[] paObject;
	paObject = NULL;
	_size = 0;
} //end ArrayClass destructor

template <class DataType>
ArrayClass<DataType>::ArrayClass(int n, const DataType& val)
{
	_size = 0; //default in case allocation fails
	paObject = new DataType[n];
	if (paObject == NULL) throw ArrayMemoryException(); //Array does not fit into available memory
	_size = n;
	for (int i = 0; i < n; i++)
		paObject[i] = val;
} //end ArrayClass constructor with n & val

template <class DataType>
ArrayClass<DataType>::ArrayClass(const ArrayClass<DataType>& ac)
{
	if (&ac != this) //disallow copying the object on to itself
		copy(ac);
} //end copy constructor

template <class DataType>
int ArrayClass<DataType>::size() const
{
	return _size;
} //end size

template <class DataType>
void ArrayClass<DataType>::copy(const ArrayClass<DataType>& ac)
{
	_size = 0; //default in case allocation fails
	paObject = new DataType[ac._size];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = ac._size;
	for (int i = 0; i < _size; i++)
	{
		paObject[i] = ac.paObject[i];
	}
} //end copy method

template <class DataType>
void ArrayClass<DataType>::operator= (const ArrayClass<DataType>& ac)
{
	if (&ac != this) //disallow copying the object onto itself
	{
		if (paObject != NULL)delete[] paObject;
		copy(ac);
	}
} //end overloaded =

template <class DataType>
DataType& ArrayClass<DataType>::operator[] (int k)
{
	if ((k < 0) || (k >= size())) throw ArrayBoundsException();
	return paObject[k];
} //end overloaded []
#endif