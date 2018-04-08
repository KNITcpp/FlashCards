#include <gtest/gtest.h>
#include "Flashcard.h"
#include "Round.h"
#include "StudyMode.h"

class FakeAlwaysTrueStudyMode : public StudyMode
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
	FakeAlwaysTrueStudyMode mode;
	Round round;
};


TEST_F(ARound, HasZeroCardsToGoWhenCreated)
{
	ASSERT_EQ(round.cardsToGo(), 0);
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
	FakeAlwaysTrueStudyMode mode;
	Round round;
};


TEST_F(ARoundWithOneFlashcard, isNoLongerEmptyAfterFlashcardsAdded)
{
	ASSERT_FALSE(round.isEmpty());
}


TEST_F(ARoundWithOneFlashcard, HasOneCardToGo)
{
	ASSERT_EQ(round.cardsToGo(), 1);
}


TEST_F(ARoundWithOneFlashcard, PlaysTheCard)
{
	round.play();

	ASSERT_EQ(flashcards[0].getLastUsages().size(), 1);
}

TEST_F(ARoundWithOneFlashcard, InvokesStudyMode)
{
	round.play();

	EXPECT_TRUE(mode.wasInvoked());
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
	FakeAlwaysTrueStudyMode mode;
	Round round;
};

TEST_F(ARoundWithTwoFlashcards, PlaysTheFirstCard)
{
	round.play();

	ASSERT_EQ(flashcards[0].getLastUsages().size(), 1);
}


TEST_F(ARoundWithTwoFlashcards, PlaysAllCards)
{
	round.play();

	ASSERT_EQ(flashcards[0].getLastUsages().size(), 1);
	ASSERT_EQ(flashcards[1].getLastUsages().size(), 1);
}

TEST(ARoundWithNullptrMode, ThrowsLogicException)
{
	std::vector<Flashcard> flashcards;

	ASSERT_THROW(Round(flashcards, nullptr), std::logic_error);
}