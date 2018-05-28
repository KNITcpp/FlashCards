#include <gtest/gtest.h>
#include "Flashcard.h"
#include "Round.h"
#include "StudyMode.h"

#include <chrono>
#include <thread>

class MockAlwaysReturningBadAnswerStudyMode : public StudyMode
{
public:
	static void simulatePlayerAnswerTime()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	bool performFlashcard(const Flashcard& flashcard) override
	{
		simulatePlayerAnswerTime();
		return false;
	}
};


class ARoundWithAlwaysBadAnswer : public ::testing::Test
{
public:
	ARoundWithAlwaysBadAnswer() : round(flashcards, &mode) {};
	void SetUp() override
	{
		flashcards.emplace_back("word", "translation");
		flashcards.emplace_back("word1", "translation1");
	}
	std::vector<Flashcard> flashcards;
	MockAlwaysReturningBadAnswerStudyMode mode;
	Round round;
};


TEST_F(ARoundWithAlwaysBadAnswer, AddsBadAnswerToFlashcards)
{
	round.play();

	ASSERT_GT(flashcards[0].getBadAnswers(), 0);
	ASSERT_GT(flashcards[1].getBadAnswers(), 0);
}


TEST_F(ARoundWithAlwaysBadAnswer, PlaysEveryBadAnsweredFlashcardMoreThanOnce)
{
	round.play();

	ASSERT_GT(flashcards[0].getBadAnswers(), 1);
	ASSERT_GT(flashcards[1].getBadAnswers(), 1);
}


TEST_F(ARoundWithAlwaysBadAnswer, PlaysEveryBadAnsweredFlashcardExactlyThreeTimes)
{
	auto firstCardBefore = flashcards[0];
	auto secondCardBefore = flashcards[1];

	round.play();

	ASSERT_EQ(flashcards[0].getBadAnswers(), firstCardBefore.getBadAnswers()+3);
	ASSERT_EQ(flashcards[1].getBadAnswers(), secondCardBefore.getBadAnswers()+3);
}


TEST_F(ARoundWithAlwaysBadAnswer, PlaceBadAnsweredCardInNewPlaceInRound)
{
	const Flashcard& firstCard = flashcards[0];
	const Flashcard& secondCard = flashcards[1];

	round.play();

	ASSERT_GT(firstCard.getLastUsages()[1], secondCard.getLastUsages()[0]);
}




class ARoundWithAlwaysBadAnswerAndPreloadedStatistics: public ::testing::Test
{
public:
	ARoundWithAlwaysBadAnswerAndPreloadedStatistics() : round(flashcards, &mode) {};
	void SetUp() override
	{
		flashcards.emplace_back("word", "translation", 3, 6);
		flashcards.emplace_back("word1", "translation1", 4, 5);
	}
	std::vector<Flashcard> flashcards;
	MockAlwaysReturningBadAnswerStudyMode mode;
	Round round;
};

TEST_F(ARoundWithAlwaysBadAnswerAndPreloadedStatistics, AddsBadAnswerToFlashcards)
{
	round.play();

	ASSERT_GT(flashcards[0].getBadAnswers(), 0);
	ASSERT_GT(flashcards[1].getBadAnswers(), 0);
}

TEST_F(ARoundWithAlwaysBadAnswerAndPreloadedStatistics, PlaysEveryBadAnsweredFlashcardExactlyThreeTimes)
{
	const Flashcard& firstCard = flashcards[0];
	const Flashcard& secondCard = flashcards[1];

	round.play();

	ASSERT_GT(firstCard.getLastUsages()[1], secondCard.getLastUsages()[0]);
}

TEST_F(ARoundWithAlwaysBadAnswerAndPreloadedStatistics, PlaceBadAnsweredCardInNewPlaceInRound)
{
	const Flashcard& firstCard = flashcards[0];
	const Flashcard& secondCard = flashcards[1];

	round.play();

	ASSERT_GT(firstCard.getLastUsages()[1], secondCard.getLastUsages()[0]);
}