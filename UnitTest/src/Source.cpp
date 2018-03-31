#include "gtest/gtest.h"
#include <cstdio>

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
	int result=RUN_ALL_TESTS();
	//std::getchar();
	return result;
}

TEST(testing, testing)
{
	ASSERT_TRUE(true);
}