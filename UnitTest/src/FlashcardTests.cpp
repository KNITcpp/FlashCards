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
const std::string FlashcardTest::translation = "vizualny";


TEST_F(FlashcardTest, getWord)
{
	EXPECT_EQ(word, fc.getWord());
}

TEST_F(FlashcardTest, getTranslation)
{
	EXPECT_EQ(translation, fc.getTranslation());
}

TEST_F(FlashcardTest, getGoodAnswers)
{
	EXPECT_EQ(goodAnswers, fc.getGoodAnswers());
}

TEST_F(FlashcardTest, getBadAnswers)
{
	EXPECT_EQ(badAnswers, fc.getBadAnswers());
}

TEST_F(FlashcardTest, addGoodAnswer)
{
	fc.addGoodAnswer();
	EXPECT_EQ(goodAnswers + 1, fc.getGoodAnswers());
}

TEST_F(FlashcardTest, addBadAnswer)
{
	fc.addBadAnswer();
	EXPECT_EQ(badAnswers + 1, fc.getBadAnswers());
}

TEST_F(FlashcardTest, CopyConstructor)
{
	Flashcard fc1(fc);
	EXPECT_EQ(fc1.getWord(), fc.getWord());
	EXPECT_EQ(fc1.getTranslation(), fc.getTranslation());
	EXPECT_EQ(fc1.getGoodAnswers(), 0);
	EXPECT_EQ(fc1.getBadAnswers(), 0);
} 