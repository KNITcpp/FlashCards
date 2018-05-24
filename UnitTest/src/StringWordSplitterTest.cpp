#include <gtest/gtest.h>
#include "StringWordSplitter.h"

TEST(AStringWordSplitter, AlwaysSplitAllWords)
{
	const std::wstring STRING_TO_SPLIT = L"      something     to be splited ";
	const int WORDS_IN_STRING_TO_SPLIT=4;

	StringWordSplitter splitter(STRING_TO_SPLIT);

	ASSERT_NE(splitter.size(), 0);
	EXPECT_EQ(splitter.size(), WORDS_IN_STRING_TO_SPLIT);
	
	EXPECT_EQ(splitter[0], L"something");
	EXPECT_EQ(splitter[1], L"to");
	EXPECT_EQ(splitter[2], L"be");
	EXPECT_EQ(splitter[3], L"splited");
}

