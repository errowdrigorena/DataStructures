/*
 * Node_loops.cc
 *
 *  Created on: Jan 12, 2022
 *      Author: iban
 */

//this is a typical question about how to handle loops inside SSLs.
//I truly believe that the best way is avoiding it inside the structure.
//Some approaches will be discussed in those tests
#include <Singly_linked_list/Node_singly_linked_list.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <set>

using Node = Node_singly_linked_list<int>;

class Node_loops_fixture: public testing::Test
{
  public:
   Node_loops_fixture();
   virtual ~Node_loops_fixture();
  protected:
   int number_of_nodes_;
   Node* node_5_;
   Node* node_4_;
   Node* node_3_;
   Node* node_2_;
   Node* node_1_;

   void connect_5_to_2();
};

Node_loops_fixture::Node_loops_fixture() : number_of_nodes_{5 }, node_5_{new Node(5) },
    node_4_{new Node(4, node_5_) }, node_3_{new Node(3, node_4_) }, node_2_{new Node(2, node_3_) },
    node_1_{new Node(1, node_2_) }
{
  ; //do nothing. This creates 1->2->3->4->5->nullptr
}

Node_loops_fixture::~Node_loops_fixture()
{
  delete node_5_;
  delete node_4_;
  delete node_3_;
  delete node_2_;
  delete node_1_;
}

void Node_loops_fixture::connect_5_to_2()
{
  node_5_->next_ = node_2_; //This enforces 1->2->3->4->5-|
			    //                 ^----------|
}

//simple approach. If we can reach to the last node, it is not a loop.
//inefficient, but it works
bool is_loop_with_size_approach(Node* first_node, std::size_t number_of_nodes)
{
  std::size_t i;
  auto actual_node = first_node;
  for(i = 0; i <= number_of_nodes && actual_node!=nullptr; i++)
    {
      actual_node = actual_node->next_;
    }

  bool is_loop{i >  number_of_nodes};
  return is_loop;
}

TEST_F(Node_loops_fixture, Test_Size_Approach)
{
  EXPECT_EQ(is_loop_with_size_approach(node_1_, number_of_nodes_), false);
  connect_5_to_2();
  EXPECT_EQ(is_loop_with_size_approach(node_1_, number_of_nodes_), true);
}


//in college it is said that at some point, if it is a loop
//it will reach to the first node. A constrain
//of 25 hoops is considered for this test suite.
bool is_loop_with_first_node_approach(Node* first_node)
{
  auto actual_node = first_node;
  for(std::size_t i = 0; i < 1000 && actual_node->next_ == first_node; i++)
    {
      actual_node = actual_node->next_;
    }

  bool is_loop{actual_node->next_ ==  first_node};
  return is_loop;
}

TEST_F(Node_loops_fixture, Test_First_Node_Approach)
{
  EXPECT_EQ(is_loop_with_first_node_approach(node_1_), false);
  connect_5_to_2();
  //EXPECT_EQ(is_loop_with_first_node_approach(node_1_), true); // this test fails discoment in order to show the result
}

//Another way is to check if the address of memory has been already used.
//With a vector checking it is slow
bool is_loop_with_address_vector_approach(Node* first_node)
{
  std::vector<Node*> addresses;
  auto actual_node=first_node;

  auto is_loop{false };
  while ( actual_node != nullptr && is_loop == false )
    {
      auto it = std::find(addresses.begin(), addresses.end(), actual_node); //equivalent to a for/while loop
      if( it !=  addresses.end() )
	{
	  is_loop = true;
	}
      else
	{
	  addresses.push_back(actual_node);
	  actual_node = actual_node->next_;
	}
    }
  return is_loop;
}

TEST_F(Node_loops_fixture, Test_Address_Vector_Approach)
{
  EXPECT_EQ(is_loop_with_address_vector_approach(node_1_), false);
  connect_5_to_2();
  EXPECT_EQ(is_loop_with_address_vector_approach(node_1_), true);
}

//As before another way is to check if the address of memory has been already used.
//BR trees (or another balanced tree) are (set) are faster but
//1- It cannot be guaranteed that the implementation isn't a linked list (if it is, it doesn't make sense)
//2- They still consume memory
bool is_loop_with_address_set_approach(Node* first_node)
{
  std::set<Node*> addresses;
  auto actual_node=first_node;

  auto is_loop{false };
  while ( actual_node != nullptr && is_loop == false )
    {
      auto it = addresses.find(actual_node); //equivalent to a for/while loop
      if( it !=  addresses.end() )
	{
	  is_loop = true;
	}
      else
	{
	  addresses.insert(actual_node);
	  actual_node = actual_node->next_;
	}
    }
  return is_loop;
}

TEST_F(Node_loops_fixture, Test_Address_Set_Approach)
{
  EXPECT_EQ(is_loop_with_address_set_approach(node_1_), false);
  connect_5_to_2();
  EXPECT_EQ(is_loop_with_address_set_approach(node_1_), true);
}

