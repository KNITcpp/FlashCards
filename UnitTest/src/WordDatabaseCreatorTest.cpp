#include <gtest/gtest.h>
#include "WordDatabaseCreator.h"
#include <vector>

void testIfWordWithFreqInside(std::unordered_map<std::wstring/*word*/, int /*occurences*/> database, std::wstring word, int frequency)
{
	auto iter = database.find(word);
	ASSERT_NE(iter, database.end());
	EXPECT_EQ(iter->second, frequency);
}

TEST(AWordDatabaseCreator, AlwaysReturnsNothingAfterBeingConstructed)
{
	WordDatabaseCreator database;
	std::unordered_map<std::wstring/*word*/, int /*occurences*/> wordWithFreq = database.getWords();
	ASSERT_EQ(wordWithFreq.size(), 0);
}

TEST(AWordDatabaseCreator, AlwaysProcessesAllWordsIfRegexNotSet)
{
	WordDatabaseCreator database;
	std::wstring exampleText= L"one one one two three four four five six six";

	database.process(exampleText);
	std::unordered_map<std::wstring/*word*/, int /*occurences*/> occuredWords = database.getWords();
	ASSERT_NE(occuredWords.size(), 0);
	EXPECT_EQ(occuredWords.size(), 6);

	testIfWordWithFreqInside(occuredWords, L"one", 3);
	testIfWordWithFreqInside(occuredWords, L"two", 1);
	testIfWordWithFreqInside(occuredWords, L"three", 1);
	testIfWordWithFreqInside(occuredWords, L"four", 2);
	testIfWordWithFreqInside(occuredWords, L"five", 1);
	testIfWordWithFreqInside(occuredWords, L"six", 2);
}




//TODO: test case insensitivity
//TODO: add regexes