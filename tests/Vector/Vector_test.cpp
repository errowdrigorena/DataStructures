/*
 * Vector_test.cpp
 *
 *  Created on: Dec 18, 2021
 *      Author: iban
 */
#include <gtest/gtest.h>
#include <Vector/Myvector.h>

#include <iostream>

TEST(My_Vector_Test, Test_Init_List_Creation)
{
	My_vector<int> vector_int_1_2_3{1, 2, 3};
	My_vector<bool> vector_bool_true_false{true, false};

	for(int i=0; i<3; i++)
	{
		ASSERT_EQ(vector_int_1_2_3[i], i+1);
	}

	EXPECT_EQ(vector_bool_true_false[0], true);
	EXPECT_EQ(vector_bool_true_false[1], false);

}

TEST(My_Vector_Test, Test_Empty)
{
	My_vector<int> vector_int_empty{};
	EXPECT_EQ(vector_int_empty.empty(), true);
	My_vector<int> vector_int_not_empty{1, 2};
	EXPECT_EQ(vector_int_not_empty.empty(), false);

}

TEST(My_Vector_Test, Test_Front)
{
	My_vector<int> vector_int_0_1{0, 1};
	EXPECT_EQ(vector_int_0_1.front(), 0);
}

TEST(My_Vector_Test, Test_Back)
{
	My_vector<int> vector_int_0_1{0, 1};
	EXPECT_EQ(vector_int_0_1.back(), 1);
}

TEST(My_Vector_Test, Test_Push_Back)
{
	std::cout << "In Test push back: " << std::endl;
	My_vector<int> vector_int_1_2_3{1, 2, 3};

	for(int i=4; i <= 16; i++) //it will increase size 2 times doing so
	{
		vector_int_1_2_3.push_back(i);
	}

	for(int i=0; i < 16; i++)
	{
		EXPECT_EQ(vector_int_1_2_3[i], i+1);
	}
}

TEST(My_Vector_Test, Test_Out_of_bound)
{
	std::cout << "In Test push back: " << std::endl;
	My_vector<int> vector_int_1_2_3{1, 2, 3};
	EXPECT_THROW(vector_int_1_2_3[3], std::invalid_argument);
	EXPECT_NO_THROW(vector_int_1_2_3[2]);
    EXPECT_THROW(vector_int_1_2_3[-1], std::invalid_argument);
}

TEST(My_Vector_Test, Test_Forward_Iteration)
{
	My_vector<int> vector_int_1_2{1, 2};

	int i{0 };
	for(auto it = vector_int_1_2.begin(); it !=vector_int_1_2.end(); it++)
	{
		i++;
		EXPECT_EQ(*it, i);
	}

	i=0;
	for(auto value : vector_int_1_2)
	{
		i++;
		EXPECT_EQ(value, i);
	}
}

TEST(My_Vector_Test, Test_Backward_Iteration)
{
	My_vector<int> vector_int_1_2_3{1, 2, 3};
	int i={3};
	for(auto it = vector_int_1_2_3.rbegin(); it != vector_int_1_2_3.rend(); it++)
	{
		EXPECT_EQ(*it, i);
		i--;
	}
}

TEST(My_Vector_Test, Test_Initialitation_Assigment)
{
	My_vector<int> vector_int_1_2={1, 2};

	int i{0 };
	for(auto it = vector_int_1_2.begin(); it !=vector_int_1_2.end(); it++)
	{
		i++;
		EXPECT_EQ(*it, i);
	}
}
