#include <gtest/gtest.h>
#include "FirstElementInjector.h"

using priority = int;
using  index = size_t;


class AFirstElementInjectorWithNoCards : public ::testing::Test
{
public:
	std::vector<size_t> cardsToPlay;
	void SetUp() override
	{

	}
};

TEST_F(AFirstElementInjectorWithNoCards, ThrowsLogicExceptionWhenEmpty)
{
	ASSERT_THROW(FirstElementInjector::inject(cardsToPlay), std::logic_error);
}



class AFirstElementInjectorWithOneCards : public ::testing::Test
{
public:
	std::vector<size_t> cardsToPlay;
	void SetUp() override
	{
		cardsToPlay.push_back(firstCardIndex);
	}
	size_t firstCardIndex = 0;
};

TEST_F(AFirstElementInjectorWithOneCards, LeavesElementAtFirstPosition)
{
	FirstElementInjector::inject(cardsToPlay);

	ASSERT_EQ(cardsToPlay[0], firstCardIndex);
}



class AFirstElementInjectorWithManyCards : public ::testing::Test
{
public:
	std::vector<size_t> cardsToPlay;
	void SetUp() override
	{
		cardsToPlay.push_back(firstCardIndex);
		cardsToPlay.push_back(1);
		cardsToPlay.push_back(2);
		cardsToPlay.push_back(3);
	}
	size_t firstCardIndex = 0;
};


TEST_F(AFirstElementInjectorWithManyCards, ChangesFirstElementPosition)
{
	const auto numOfCardsToPlayBeforePlacing = cardsToPlay.size();

	FirstElementInjector::inject(cardsToPlay);

	ASSERT_NE(cardsToPlay[0], firstCardIndex);
}

TEST_F(AFirstElementInjectorWithManyCards, PutsElementInVectorAtCountedPosition)
{
	auto i = FirstElementInjector::countPosition(cardsToPlay);

	FirstElementInjector::inject(cardsToPlay);
	

	ASSERT_EQ(cardsToPlay[i], firstCardIndex);
}