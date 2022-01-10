#include <iostream>
#include <gtest/gtest.h>
#include <Singly_linked_list/My_Singly_linked_list.h>

class Singly_linked_list_fixture: public testing::Test
{
  public:
   Singly_linked_list_fixture();
   virtual ~Singly_linked_list_fixture();
   void SetUp() override;
   void TearDown() override;
   static void SetUpTestCase();
   static void TearDownTestCase();
  protected:
   My_Singly_linked_list<int> msll_;
};

Singly_linked_list_fixture::Singly_linked_list_fixture()
{
  std::cout << "Constructor called\n";
}
