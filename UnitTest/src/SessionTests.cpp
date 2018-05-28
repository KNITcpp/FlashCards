#include <gtest/gtest.h>

#include  "Session.h"

class FakeStudyMode : public StudyMode
{
public:
	bool performFlashcard(const Flashcard& flashcard) override
	{
		return true;
	}
};

class ASessionWithOneCard : public ::testing::Test
{
public:
	std::vector<Flashcard> flashcards;
	FakeStudyMode mode;
	Session session;

	ASessionWithOneCard() : session(flashcards, &mode) {};

	void SetUp() override
	{
		flashcards.emplace_back("word", " translation");
	}
};


TEST_F(ASessionWithOneCard, playsTheCard)
{
	session.play();

	ASSERT_GT(flashcards[0].getLastUsages().size(), 0);

}

TEST_F(ASessionWithOneCard, hasOneRound)
{
	session.setRoundLength(1);
	session.play();

	EXPECT_EQ(session.getNumOfRounds(), 1);
}


TEST(ASessionWithThreeCards, splitsFlashcardsIntoThreeRounds)
{
	std::vector<Flashcard> flashcards;
	FakeStudyMode mode;
	flashcards.emplace_back("word1", "translation1");
	flashcards.emplace_back("word2", "translation2");
	flashcards.emplace_back("word3", "translation3");
	Session session(flashcards, &mode);
	session.setRoundLength(1);

	session.play();

	ASSERT_EQ(session.getNumOfRounds(), 3);
}