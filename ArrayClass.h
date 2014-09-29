#ifndef __ARRAYCLASS__H
#define __ARRAYCLASS__H

#include "AbstractArray.h"

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

template <class DataType>
class ArrayClass : virtual public AbstractArrayClass < DataType >
{
protected:
	DataType* paObject;
	int _size;
	void copy(const ArrayClass<DataType>& ac);
public:
	ArrayClass();
	ArrayClass(int n);
	ArrayClass(int n, const DataType& val);
	ArrayClass(const ArrayClass<DataType>& ac);
	virtual ~ArrayClass();
	virutal int size() const;
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
#endif