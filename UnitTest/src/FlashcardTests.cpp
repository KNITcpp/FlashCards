#include <gtest/gtest.h>
#include "Flashcard.h"


class FlashcardTest : public ::testing::Test
{
public:
	FlashcardTest() : fc(word, translation, goodAnswers, badAnswers) {}
	static const std::string word;
	static const std::string translation;
	static const int goodAnswers = 10;
	static const int badAnswers = 3;

	Flashcard fc;
};

const std::string FlashcardTest::word = "visual";
const std::string FlashcardTest::translation = "wizualny";


TEST_F(FlashcardTest, getWord_WhenCalled_ReturnsWordValue)
{
	EXPECT_EQ(word, fc.getWord());
}

TEST_F(FlashcardTest, getTranslation_WhenCalled_ReturnsTranslationValue)
{
	EXPECT_EQ(translation, fc.getTranslation());
}

TEST_F(FlashcardTest, getGoodAnswers_ByDefault_ReturnsZero)
{
	Flashcard fc1("", "");
	EXPECT_EQ(0, fc1.getGoodAnswers());
}

TEST_F(FlashcardTest, getGoodAnswers_WhenCalled_ReturnsGoodAnswersValue)
{
	EXPECT_EQ(goodAnswers, fc.getGoodAnswers());
}

TEST_F(FlashcardTest, getBadAnswers_ByDefault_ReturnsZero)
{
	Flashcard fc1("", "");
	EXPECT_EQ(0, fc1.getBadAnswers());
}

TEST_F(FlashcardTest, getBadAnswers_WhenCalled_ReturnsBadAnswersValue)
{
	EXPECT_EQ(badAnswers, fc.getBadAnswers());
}

TEST_F(FlashcardTest, getLastUsages_WhenCalled_ReturnsTimeVector)
{
	timeVector tv;
	EXPECT_EQ(tv, fc.getLastUsages());
}

TEST_F(FlashcardTest, addGoodAnswer_WhenCalled_IncrementsGoodAnswersValue)
{
	fc.addGoodAnswer();
	EXPECT_EQ(goodAnswers + 1, fc.getGoodAnswers());
}

TEST_F(FlashcardTest, addBadAnswer_WhenCalled_IncrementsBadAnswersValue)
{
	fc.addBadAnswer();
	EXPECT_EQ(badAnswers + 1, fc.getBadAnswers());
}

TEST_F(FlashcardTest, addUsage_WhenCalled_InsertsElemntIntoLastUsages)
{
	std::chrono::system_clock::time_point epochTime;
	fc.addUsage(epochTime);
	timeVector tv = fc.getLastUsages();
	EXPECT_EQ(epochTime, tv.back());
}