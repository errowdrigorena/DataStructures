/*
 * Advanced_sll_tect.cc
 *
 *  Created on: Jan 13, 2022
 *      Author: iban
 */
#include <Singly_linked_list/My_advanced_sll.h>
#include <gtest/gtest.h>
#include <vector>

class Advanced_linked_list_fixture: public testing::Test
{
  public:
  Advanced_linked_list_fixture();
   virtual ~Advanced_linked_list_fixture(){};
  protected:
   My_advanced_sll<int> mall_;
};

Advanced_linked_list_fixture::Advanced_linked_list_fixture() : mall_{100,2,1,4,3,5,25,6,5,0}
{
  ; //do nothing
}

TEST_F(Advanced_linked_list_fixture, Test_get_max)
{
  auto it = mall_.get_max();
  EXPECT_EQ(it->value_, 100);
  EXPECT_EQ(it->next_, mall_.begin()->next_);
  mall_.erase_first_ocurrence(100);
  it = mall_.get_max();
  EXPECT_EQ(it->value_, 25);
}

TEST_F(Advanced_linked_list_fixture, Test_get_min)
{
  auto it = mall_.get_min();
  EXPECT_EQ(it->value_, 0);
  EXPECT_EQ(it->next_, nullptr);
  mall_.erase_first_ocurrence(0);
  it = mall_.get_min();
  EXPECT_EQ(it->value_, 1);
}

TEST_F(Advanced_linked_list_fixture, Test_sorted_by_value)
{
  std::vector<int> expected_values_ascendant{0,1,2,3,4,5,5,6,25,100 };
  mall_.sort_by_value();

  for(std::size_t i = 0; i < expected_values_ascendant.size(); i++)
    {
      EXPECT_EQ(mall_[i], expected_values_ascendant[i]);
    }

  std::vector<int> expected_values_descendant{100,25,6,5,5,4,3,2,1,0 };
  mall_.sort_by_value(std::greater<int>());

  for(std::size_t i = 0; i < expected_values_descendant.size(); i++)
    {
      EXPECT_EQ(mall_[i], expected_values_descendant[i]);
    }
}

TEST_F(Advanced_linked_list_fixture, Test_sorted_by_node)
{
  auto it_100 = mall_.begin();
  auto it_0 = it_100;
  std::advance(it_0, 9);
  EXPECT_EQ(it_0->value_, 0);
  EXPECT_EQ(it_100->value_, 100);

  std::vector<int> expected_values_ascendant{0,1,2,3,4,5,5,6,25,100 };
  mall_.sort_by_node();

  for(std::size_t i = 0; i < expected_values_ascendant.size(); i++)
    {
      EXPECT_EQ(mall_[i], expected_values_ascendant[i]);
    }

  EXPECT_EQ(mall_.begin(), it_0);

  std::vector<int> expected_values_descendant{100,25,6,5,5,4,3,2,1,0 };
  mall_.sort_by_node(std::greater<int>());

  for(std::size_t i = 0; i < expected_values_descendant.size(); i++)
    {
      EXPECT_EQ(mall_[i], expected_values_descendant[i]);
    }

  EXPECT_EQ(mall_.begin(), it_100);

}
