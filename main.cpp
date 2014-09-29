#include "ArrayClass.h"
#include "Vector.h"
#include "String.h"
#include "TextField.h"
#include "BibEntry.h"
void main()
{
	//--------------------------------------------------------ArrayClass testing
	ArrayClass<int> ai(5, 4);
	ArrayClass<int> ai2 = ai;
	ArrayClass<int> ai3(10);
	ArrayClass<TextField> fields;
	fields = ArrayClass<TextField>(20);
	cout << fields << endl;
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


	//--------------------------------------------------BibEntry testing
	BibEntry bib("article", "latilla_hello");
	TextField test("bob", "42");
	bib.addField(test);
	cout << bib << endl;

	while (true) {};
} //end main