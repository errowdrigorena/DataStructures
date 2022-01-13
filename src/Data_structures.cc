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
#include <Singly_linked_list/My_Singly_linked_list.h>
#include <Singly_linked_list/My_advanced_sll.h>
#include <functional>

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

	/*My_Singly_linked_list<int> my_list{1, 2, 3};
	cout << endl << endl;
	cout << my_list;
	cout << "insert a seven" << endl;

	my_list[2] = 7;
	cout << "seven inserted" << endl;

	cout << endl << endl;

	cout << my_list;

	my_list.push_back(5);
	my_list.push_back(8);
	my_list.push_front(0);

	cout << my_list;

	cout << "before for " << endl;
	for( auto val : my_list)
	{
	    cout << val.value_ << " ";
	}

	cout <<endl;
	cout << "PRINT MSLL" << endl;
	cout <<endl << endl << endl;


	My_Singly_linked_list<int> msll1 = my_list;
	My_Singly_linked_list<int> msll_;
	msll_={1,2,3,4,5,5,2,6,5,0,5};

	for( auto val : msll_)
	{
	    cout << val.value_ << " ";
	}
	cout <<endl << endl << endl;

	msll_.erase_first_ocurrence(2);

	for( auto val : msll_)
	{
	    cout << val.value_ << " ";
	}

	cout <<endl << endl << endl;

	msll_.erase_every_ocurrence(5);

	for( auto val : msll_)
	{
	    cout << val.value_ << " ";
	}

	cout <<endl << endl << endl;*/


	/*My_Singly_linked_list<int> my_list8{1, 1, 2, 3, 1, 3, 2, 5, 5, 6, 6};
	my_list8.erase_reps();
	for( auto val : my_list8)
	{
	    cout << val.value_ << " ";
	}

	cout <<endl << endl << endl;*/

	/*My_Singly_linked_list<int> my_list8{1,2,3,4,5,5,2,6,5,0};
	my_list8.erase_every_ocurrence(5);
	cout << my_list8 << endl;
	cout << 1 << endl << "Finish" << endl;*/

	My_advanced_sll<int> my_assl{100,2,1,4,3,5,25,6,5,0};
	/*int one = 1;
	int two = 2;
	//auto out = std::max<int>(one,two);

	auto evaluation_getter = [&](std::function<bool(int,int)>comparer )->int
	    {
	      int eval = one;
	      if( comparer(one, two ) )
		{
		  eval = two;
		}
	      return eval;
	    };

	auto first = evaluation_getter(std::greater<int>());
	auto second = evaluation_getter(std::less<int>());
	cout << "The FIRST is: " << first << endl;
	cout << "The SECOND is: " << second << endl;*/

	//cout << "std::greater(1,2) = " << std::boolalpha << std::greater(1, 2) << std::endl;
	cout << "before operation" << endl;

	auto it = my_assl.find_prev();

	if(it == my_assl.end())
	  {
	    cout << "as expected" << endl;
	  }
	else
	  {
	    cout << "QUITE UNexpected" << endl;

	  }
	cout << "after operation" << endl;

	auto min = my_assl.get_min();
	auto max = my_assl.get_max();
	cout << "The min is: " << min->value_ << endl;
	cout << "The max is: " << max->value_ << endl;

	cout << my_assl << endl;

	cout << "my_assl will bee sorted" << endl;
	my_assl.sort_by_node( std::greater<int>() );
	cout << "my_assl has been sorted" << endl;
	cout << my_assl << endl;

	cout << "my_assl will bee sorted, again" << endl;
	my_assl.sort_by_node();
	cout << my_assl << endl;
	return 0;
}
