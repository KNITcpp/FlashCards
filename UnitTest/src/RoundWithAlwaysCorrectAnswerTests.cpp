#include <gtest/gtest.h>
#include "Flashcard.h"
#include "Round.h"
#include "StudyMode.h"

class MockAlwaysTrueStudyMode : public StudyMode
{
public:
	bool performFlashcard(const Flashcard& flashcard) override
	{
		return true;
	}
};


class ARoundWithAlwaysCorrectAnswer : public ::testing::Test
{
public:
	ARoundWithAlwaysCorrectAnswer() : round(flashcards, &mode) {};
	void SetUp() override
	{
		flashcards.emplace_back("word", "translation");
		flashcards.emplace_back("word1", "translation1");
	}
	std::vector<Flashcard> flashcards;
	MockAlwaysTrueStudyMode mode;
	Round round;
};

TEST_F(ARoundWithAlwaysCorrectAnswer, AddsGoodAnswerToFlashcardOnlyOnce)
{
	round.play();

	ASSERT_EQ(flashcards[0].getGoodAnswers(), 1);
	ASSERT_EQ(flashcards[1].getGoodAnswers(), 1);
}
