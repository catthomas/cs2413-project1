#include "ArrayClass.h"
void main()
{
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

	while (true){};
} //end main