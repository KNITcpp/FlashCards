#include <gtest/gtest.h>
#include "Flashcard.h"
#include "Round.h"
#include "StudyMode.h"

class MockDoNothingStudyMode : public StudyMode
{
public:
	bool performFlashcard(const Flashcard& flashcard) override
	{
		wasInvoked_ = true;
		return true;
	}
	bool wasInvoked() const { return wasInvoked_; }
private:
	bool wasInvoked_ = false;
};


class ARound : public ::testing::Test
{
public:
	ARound() : round(flashcards, &mode) {}
public:
	std::vector<Flashcard> flashcards;
	MockDoNothingStudyMode mode;
	Round round;
};


TEST_F(ARound, HasZeroCardsInRoundWhenCreated)
{
	ASSERT_EQ(round.cardsInRound(), 0);
}


TEST_F(ARound, IsEmptyWhenCreated)
{
	ASSERT_TRUE(round.isEmpty());
}



class ARoundWithOneFlashcard : public ::testing::Test
{
public:
	ARoundWithOneFlashcard() : round(flashcards, &mode) {};
	void SetUp() override
	{
		flashcards.emplace_back("word", "translation");
	}
	std::vector<Flashcard> flashcards;
	MockDoNothingStudyMode mode;
	Round round;
};


TEST_F(ARoundWithOneFlashcard, isNoLongerEmptyAfterFlashcardsAdded)
{
	ASSERT_FALSE(round.isEmpty());
}


TEST_F(ARoundWithOneFlashcard, HasOneCardInRound)
{
	ASSERT_EQ(round.cardsInRound(), 1);
}


TEST_F(ARoundWithOneFlashcard, PlaysTheCard)
{
	round.play();

	ASSERT_EQ(flashcards[0].getLastUsages().size(), 1);
}

TEST_F(ARoundWithOneFlashcard, InvokesStudyMode)
{
	round.play();

	ASSERT_TRUE(mode.wasInvoked());
}



class ARoundWithTwoFlashcards : public ::testing::Test
{
public:
	ARoundWithTwoFlashcards() : round(flashcards, &mode) {};
	void SetUp() override
	{
		flashcards.emplace_back("word1", "translation1");
		flashcards.emplace_back("word2", "translation2");
	}
	std::vector<Flashcard> flashcards;
	MockDoNothingStudyMode mode;
	Round round;
};


TEST_F(ARoundWithTwoFlashcards, PlaysTheFirstCard)
{
	round.play();

	ASSERT_EQ(flashcards[0].getLastUsages().size(), 1);
}


TEST_F(ARoundWithTwoFlashcards, PlaysAllCards)
{;
	round.play();

	ASSERT_EQ(flashcards[0].getLastUsages().size(), 1);
	ASSERT_EQ(flashcards[1].getLastUsages().size(), 1);
}


TEST(ARoundWithNullptrStudyMode, ThrowsLogicExceptionDuringConstruction)
{
	std::vector<Flashcard> flashcards;

	StudyMode* invalidStudyMode = nullptr;
	ASSERT_THROW(Round(flashcards, invalidStudyMode), std::logic_error);
}