#include <iostream>
#include "gtest/gtest.h"

//Tests that the Foo::Bar() method does Abc.
TEST(FooTest, MethodBarDoesAbc) {
  EXPECT_EQ(12 + 12, 24);
}

TEST(FooTestSD, MethodBarDoesAb) {
  EXPECT_EQ(12 + 11, 23);
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
