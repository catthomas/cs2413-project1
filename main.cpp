#include "ArrayClass.h"
#include "Vector.h"
#include "String.h"
void main()
{
	//--------------------------------------------------------ArrayClass testing
	ArrayClass<int> ai(5, 4);
	ArrayClass<int> ai2 = ai;
	ArrayClass<int> ai3(10);

	cout << ai << endl;
	cout << ai2 << endl;
	cout << ai3 << endl; //output varies as ai3 is uninitialized
	cout << endl;
	for (int i = 0; i < ai.size(); i++)
	{
		ai[i] = i * 2;
	}
	try
	{
		ai[5] = 10; //this line outside of try will end program
	}
	catch (ArrayBoundsException e)
	{
		cout << "Index out of bounds" << endl;
	}
	cout << endl;
	ai3 = ai;
	cout << ai << endl;
	cout << ai2 << endl;
	cout << ai3 << endl;

	//-----------------------------------------------------Vector testing
	Vector<int> v;
	cout << v << ",cap " << v.capacity() << endl;
	for (int i = 0; i < 5; i++)
	{
		v.add(5 * i);
		cout << v << ",cap " << v.capacity() << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		v.insert(-5 * i, 2 * i);
		cout << v << ",cap " << v.capacity() << endl;
	}
	for (int i = 4; i >= 0; i--)
	{
		v.remove(2 * i);
		cout << v << ",cap " << v.capacity() << endl;
	}
	for (int i = 4; i >= 0; i--)
	{
		v.remove(i);
		cout << v << ",cap " << v.capacity() << endl;
	}


	//------------------------------------------------String class test
	String s1 = "String1";
	String s2 = s1;
	s2[6] = '2';
	String s3(20);
	s3 = s1;
	String s4 = " + ";
	s3 = s3 + " + " + s2;
	cout << s1 << ", " << s2 << ", " << s3 << endl;

	while (true){};
} //end main