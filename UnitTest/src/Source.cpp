#include "gtest/gtest.h"
#include <iostream>


void forBegginers()
{
	std::cout << "You can do whatever you want\n";


	std::cout << "============================\n";
}

GTEST_API_ int main(int argc, char **argv)
{
	forBegginers();
	std::cout << ("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	std::getchar();
	return result;
}

TEST(testing, testing)
{
	ASSERT_TRUE(true);
}