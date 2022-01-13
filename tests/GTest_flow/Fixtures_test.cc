/*
 * Fixtures_test.cc
 *
 *  Created on: Jan 11, 2022
 *      Author: iban
 */
#include <iostream>
#include <gtest/gtest.h>
#include <vector>

class Example_fixture: public testing::Test
{
  public:
   Example_fixture();
   virtual ~Example_fixture();
   void SetUp() override;
   void TearDown() override;
   static void SetUpTestCase();
   static void TearDownTestCase();

  protected:
   std::vector<int> vector_;
};

Example_fixture::Example_fixture() ////don't do here anything except initializing member variables
{
  std::cout << "Example_fixture Constructor called" << std::endl;
}

Example_fixture::~Example_fixture()
{
  std::cout << "Example_fixture Destructor called" << std::endl;
}

void Example_fixture::SetUp()
{
  std::cout << "Example_fixture SetUp called" << std::endl;
  vector_={1,2,3,4,5,5,2,6,5,0 };
}

void Example_fixture::TearDown()
{
  std::cout << "Example_fixture TearDown called" << std::endl;
}

void Example_fixture::SetUpTestCase()
{
  std::cout << "Example_fixture SetUpTestCase called" << std::endl;
}

void Example_fixture::TearDownTestCase()
{
  std::cout << "Example_fixture TearDownTestCase called" << std::endl;
}

TEST_F(Example_fixture, foo)
{
  std::cout << "INSIDE FOO" << std::endl;
  EXPECT_EQ(vector_[0], 1);
}

TEST_F(Example_fixture, foo2)
{
  std::cout << "INSIDE FOO2" << std::endl;
  EXPECT_EQ(vector_[1], 2);
}
