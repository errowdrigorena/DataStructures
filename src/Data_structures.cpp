//============================================================================
// Name        : Data_structures.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include <vector>
#include <Vector/Myvector.h>
using namespace std;

int main() {
	My_vector<int> a(6);
	cout << "test a[3] " << a[3] << endl;
	a[3]=3;
	cout << "After inserting 3" << endl;
	a.push_back(8);
	cout << "After pushing 8" << endl;

	cout << a << endl;

	for(auto val = a.begin(); val != a.end(); val++)
	{
		cout << *val << endl;
	}

	cout << endl << endl;

	std::fill(a.begin(), a.end(), 66);

	for(auto val : a)
	{
		cout << val << endl;
	}

	cout << endl << endl;

	My_vector<double> b{9.5, 7.5, 8.5 };

	for_each(b.begin(), b.end(), [](double val){cout<< val << endl; } );
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	My_vector<int> experiment{1, 2, 3, 4, 5};

	for(auto val = experiment.rbegin(); val != experiment.rend(); val++)
	{
		cout << *val << endl;
	}

	cout << "last is: " << experiment.back() << endl;
	cout << "first is: " << experiment.front() << endl;
	return 0;
}
