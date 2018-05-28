#pragma comment (lib, "crypt32"); //needed for libcurl
#include "gtest/gtest.h"
#include <iostream>
#include "Round.h"


GTEST_API_ int main(int argc, char **argv)
{
	//jak chcecie cos debugowac i nie ogarniacie jeszcze testów jednostkowych to po prostu tego maina traktujcie jak najzwyklejszego maina, ale usuwajcie st¹d kod przed pushem
	//tego poni¿ej nie ruszaæ
	std::cout << ("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	//std::getchar();
	return result;
}
