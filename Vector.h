#ifndef __VECTOR__H
#define __VECTOR__H

#include "ArrayClass.h"
#include "AbstractVector.h"

/*
This is a custom-written Vector class.
The code for this class was taken from the book:
"Data Structures Featuring C++" written by Dr. Sridhar
Radhakrishnan from the University of Oklahoma.

In principal, it is an array which dynamically
allocates its size based on the number of elements.
*/

template <class DataType>
class Vector : virtual public ArrayClass<DataType>, virtual public AbstractVector < DataType >
{
protected:
	int _currSize; //number of elements of the vector
	int _incFactor; //increment factor of the vector, will add to size when it expands
public:
	Vector();
	Vector(int n);
	Vector(int n, DataType& val);
	Vector(const Vector<DataType>& v);
	Vector(const ArrayClass<DataType>& ac);
	virtual ~Vector();
	void operator= (const Vector<DataType>& v);
	void operator= (const ArrayClass<DataType>& ac);
	virtual void insert(const DataType& item, int index);
	virtual void remove(int index);
	virtual void add(const DataType& item);
	virtual int size() const;
	virtual int capacity() const;
	virtual int incFactor() const;
	virtual void setIncFactor(int f);
	void setCapacity(int c);
};

template <class DataType>
Vector<DataType>::Vector()
{
	_currSize = 0; 
	_incFactor = 5; //will increase by 5 each time
} // end default constructor
//---------------------------------------------------------
template <class DataType>
Vector<DataType>::Vector(int n)
{
	_currSize = 0;
	_incFactor = n; //will double in size 
} //end constructor with n
//--------------------------------------------------------
template <class DataType>
Vector<DataType>::Vector(int n, DataType& val) : ArrayClass<DataType>(n, val) //creates an array of capacity n
{
	_currSize = 0; //currently no elements in the vector
	_incFactor = n; //will double in size
} //end constructor with n and val
//------------------------------------------------------
template <class DataType>
Vector<DataType>::~Vector()
{
	//Do nothing - destructor method contained in ArrayClass
} //end destructor
//-----------------------------------------------------
template <class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v) : ArrayClass<DataType>(v)
{
	//Relies on ArrayClass for copying the data from the underlying array
	_currSize = v._currSize;
	_incFactor = v.incFactor();
} //end copy constructor
//---------------------------------------------------
template <class DataType>
Vector<DataType>::Vector(const ArrayClass<DataType>& ac) : ArrayClass<DataType>(ac)
{
	_currSize = ac.size();
	_incFactor = _currSize; //will double in size
} //end constructor from array
//--------------------------------------------------
template <class DataType>
void Vector<DataType>::operator= (const Vector<DataType>& v)
{
	ArrayClass<DataType>::copy(v); //copy underlying array
	_currSize = v._currSize;
	_incFactor = v.incFactor();
} //end overloaded = for vector
//---------------------------------------------------
template <class DataType>
void Vector<DataType>::operator= (const ArrayClass<DataType>& ac)
{
	ArrayClass<DataType>::copy(ac); //copy underlying array
	_currSize = ac.size();
	_incFactor = _currSize; //will double in size
} //end overloaded = for array
//---------------------------------------------------
template <class DataType>
int Vector<DataType>::size() const //override ArrayClass' size 
{
	return _currSize; //number of elements currently stored in vector
} //end size
//--------------------------------------------------
template <class DataType>
int Vector<DataType>::capacity() const
{
	return _size; //return size from arrayclass (max capacity)
} //end capacity
//-------------------------------------------------
template <class DataType>
int Vector<DataType>::incFactor() const
{
	return _incFactor;
} //end incFactor
//-----------------------------------------------
template <class DataType>
void Vector<DataType>::setIncFactor(int f)
{
	if (f >= 0) _incFactor = f;
} //end setIncFactor
//----------------------------------------------
template <class DataType>
void Vector<DataType>::setCapacity(int c)
{
	int len = _currSize;
	if (len > c) len = c; //will need to truncate
	DataType* paNew = new DataType[c]; //set array to new capacity
	if (paNew == NULL)
	{
		throw ArrayMemoryException(); //was not capable of allocating enough memory
	}
	for (int i = 0; i < len; i++)
	{
		paNew[i] = paObject[i]; //copy over elements
	}
	if (paObject != NULL)
	{
		delete[] paObject; //delete old array
	}
	paObject = paNew; //reset array pointer in ArrayClass to point to new array
	_size = c; //capacity is equal to new capacity
	if (_currSize > len)
	{
		_currSize = len; //set number of elements in vector
	}
} //end setCapacity
//--------------------------------------------
template <class DataType>
void Vector<DataType>::insert(const DataType& item, int index)
{
	if ((index < 0) || (index > _currSize))
	{
		throw ArrayBoundsException(); //insert index out of range
	}
	if (_currSize + 1 == _size)
	{
		setCapacity(_size + _incFactor); //Expand length of vector
	}
	_currSize++;
	for (int i = _currSize - 1; i > index; i--)
	{
		(*this)[i] = (*this)[i - 1]; //moves elements in array to the right by one until reaching insert location
	}
	(*this)[index] = item;
} //end insert
//----------------------------------------------
template <class DataType>
void Vector<DataType>::add(const DataType& item)
{
	insert(item, _currSize); //add to end of elements
} //end add
//----------------------------------------------
template <class DataType>
void Vector<DataType>::remove(int index)
{
	if ((index < 0) || (index >= _currSize))
	{
		throw ArrayBoundsException();
	}
	if (_currSize <= _size - _incFactor) //when differenct exceeds inc factor, decrease vector size
	{
		setCapacity(_size - _incFactor);
	}
	for (int i = index; i < _currentSize - 1; i++)
	{
		(this*)[i] = (*this)[i + 1];
	}
	_currSize--;
} //end remove
#endif