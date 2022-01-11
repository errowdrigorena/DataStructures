#include <iostream>
#include <gtest/gtest.h>
#include <Singly_linked_list/My_Singly_linked_list.h>
#include <vector>

class Singly_linked_list_fixture: public testing::Test
{
  public:
   Singly_linked_list_fixture();
   virtual ~Singly_linked_list_fixture(){};
  protected:
   My_Singly_linked_list<int> msll_;
};

Singly_linked_list_fixture::Singly_linked_list_fixture() : msll_{1,2,3,4,5,5,2,6,5,0}
{
  ; //do nothing
}

TEST_F(Singly_linked_list_fixture, Test_Front)
{
  EXPECT_EQ(msll_.front(), 1);
}

TEST_F(Singly_linked_list_fixture, Test_Back)
{
  EXPECT_EQ(msll_.back(), 0);
}

//Dangerous test that may corrupt test cases. If it gives problems comment it.
TEST_F(Singly_linked_list_fixture, Test_Push_Back)
{
  auto insertable = msll_.back() + 1;
  msll_.push_back(insertable);
  EXPECT_EQ(msll_.back(), insertable);
}

//Dangerous test that may corrupt test cases. If it gives problems comment it.
TEST_F(Singly_linked_list_fixture, Test_Push_Front)
{
  auto insertable = msll_.front() + 1;
  msll_.push_front(insertable);
  EXPECT_EQ(msll_.front(), insertable);
}

//Dangerous test that may corrupt test cases. If it gives problems comment it.
TEST_F(Singly_linked_list_fixture, Test_Find_First)
{
  auto finder = msll_.find_first(1);
  auto first = msll_.begin();
  EXPECT_EQ(finder, first);
  finder = msll_.find_first(0);
  EXPECT_EQ(finder->next_, nullptr);
}

TEST_F(Singly_linked_list_fixture, Test_Ocurrences)
{
  EXPECT_EQ(msll_.find_ocurrences(200), 0);
  EXPECT_EQ(msll_.find_ocurrences(0), 1);
  EXPECT_EQ(msll_.find_ocurrences(5), 3);
}

TEST_F(Singly_linked_list_fixture, Test_List_Assignation)
{
  std::vector<int> check{1,2,3,4,5,5,2,6,5,0 };
  for(size_t i=0; i < check.size(); i++)
    {
      EXPECT_EQ(msll_[i], check[i]);
    }
}

TEST_F(Singly_linked_list_fixture, Test_Erase_First)
{
  std::vector<int> check{1,3,4,5,5,2,6,5,0 };
  msll_.erase_first_ocurrence(2);
  for(size_t i=0; i < check.size(); i++)
    {
      EXPECT_EQ(msll_[i], check[i]);
    }
}

TEST_F(Singly_linked_list_fixture, Test_Erase_All)
{
  std::vector<int> check{1,2,3,4,2,6,0 };
  msll_.erase_every_ocurrence(5);
  for(size_t i=0; i < check.size(); i++)
    {
      EXPECT_EQ(msll_[i], check[i]);
    }
}

TEST_F(Singly_linked_list_fixture, Test_Erase_Reps)
{
  std::vector<int> check{1,3,4,2,6,5,0 };
  msll_.erase_reps();
  EXPECT_EQ(msll_.size(), check.size() );
  for(size_t i=0; i < check.size(); i++)
    {
      EXPECT_NE(msll_.find_first(msll_[i]), msll_.end());
    }
}

TEST_F(Singly_linked_list_fixture, Test_Forward_Iteration)
{
  std::vector<int> check{1,2,3,4,5,5,2,6,5,0 };
  size_t i{0 };

  for(auto it = msll_.begin(); it !=msll_.end(); it++)
  {
	  EXPECT_EQ(*it, check[i]);
	  i++;
  }
}

TEST_F(Singly_linked_list_fixture, Test_Size)
{
  EXPECT_EQ(msll_.size(), 10);
}

TEST(My_Singly_linked_list_Test, Test_Init_List_Creation)
{
  My_Singly_linked_list<int> ssl_int_1_2_3{1, 2, 3};
  My_Singly_linked_list<bool> ssl_bool_true_false{true, false};

  for(int i=0; i<3; i++)
  {
      EXPECT_EQ(ssl_int_1_2_3[i], i+1);
  }

  EXPECT_EQ(ssl_bool_true_false[0], true);
  EXPECT_EQ(ssl_bool_true_false[1], false);
}

TEST(My_Singly_linked_list_Test, Test_List_Assignation_No_Fixture)
{
  My_Singly_linked_list<int> ssl_int_1_2_3_={1, 2, 3};
  My_Singly_linked_list<bool> ssl_bool_true_false_={true, false};

  for(int i=0; i<3; i++)
  {
      EXPECT_EQ(ssl_int_1_2_3_[i], i+1);
  }

  EXPECT_EQ(ssl_bool_true_false_[0], true);
  EXPECT_EQ(ssl_bool_true_false_[1], false);
}

TEST(My_Singly_linked_list_Test, Test_Empty)
{
  My_Singly_linked_list<int> ssl_empty{};
  My_Singly_linked_list<bool> ssl_not_empty{true};

  EXPECT_EQ(ssl_empty.empty(), true);
  EXPECT_EQ(ssl_not_empty.empty(), false);
}



