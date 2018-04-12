#include "Round.h"
#include "FirstElementInjector.h"
#include <chrono>
#include "CardPlayer.h"


Round::Round(std::vector<Flashcard>& flashcards, StudyMode* studyMode) :
	flashcards_(flashcards),
	studyMode_(studyMode),
	indexesInPlayOrder_()
{
	checkResources();
}

void Round::checkResources() const
{
	if (studyMode_ == nullptr)
		throw std::logic_error("Round::play() : studyMode is nullptr");
}


size_t Round::cardsInRound() const noexcept
{
	return flashcards_.size();
}


bool Round::isEmpty() const noexcept
{
	return flashcards_.empty();
}


void Round::play()
{
	preparePlayOrder();
	setStartime();
	playAllCards();
}


void Round::preparePlayOrder()
{
	reserveSpace();
	fillPlayOrder();
}


void Round::reserveSpace()
{
	indexesInPlayOrder_.reserve(flashcards_.size());
}


void Round::fillPlayOrder()
{
	for (size_t i = 0; i < flashcards_.size(); ++i)
		indexesInPlayOrder_.push_back(i);
}


void Round::setStartime()
{
	startTime_ = std::chrono::system_clock::now();
}

void Round::playAllCards()
{
	while (isCardToPlay())
		playCard();
}


bool Round::isCardToPlay() const noexcept
{
	return !indexesInPlayOrder_.empty();
}


void Round::playCard()
{
	auto& frontCard = flashcards_[indexesInPlayOrder_[0]];
	cardPlayer_.play(frontCard,studyMode_);
	if (cardPlayer_.isAnswerCorrect())
		proceedCorrectAnswer(frontCard);
	else
		proceedBadAnswer(frontCard);
}


std::chrono::system_clock::time_point Round::getCurrentTime()  noexcept
{
	return std::chrono::system_clock::now();
}


void Round::proceedCorrectAnswer(Flashcard& frontCard)
{
	addGoodAnswer(frontCard);
	eraseFrontCardFromPlay();
}


void Round::addGoodAnswer(Flashcard& frontCard) //TODO merge addGoodAnswer and addBadAnswer into 1 function
{
	frontCard.addGoodAnswer();
}


void Round::eraseFrontCardFromPlay()
{
	indexesInPlayOrder_.erase(indexesInPlayOrder_.begin());
}


void Round::proceedBadAnswer(Flashcard& frontCard)
{
	addBadAnswer(frontCard);
	if (isValidToPlay(frontCard))
		insertFrontcardAtNewPosition();
	else
		eraseFrontCardFromPlay();
}


void Round::addBadAnswer(Flashcard& frontCard)
{
	frontCard.addBadAnswer();
}


void Round::insertFrontcardAtNewPosition()
{
	FirstElementInjector::inject(indexesInPlayOrder_);
}


bool Round::isValidToPlay(Flashcard& frontCard)
{
	return  countOccurencesInRound(frontCard) < cardReplayLimit;
}


size_t Round::countOccurencesInRound(const Flashcard& frontCard) const noexcept
{
	size_t occurInRound = 0;
	for (int i = frontCard.getLastUsages().size() - 1; i >= 0; --i)
		if (wasUsedInThisRound(frontCard, i))
			++occurInRound;
		else
			break;
	return occurInRound;
}


bool Round::wasUsedInThisRound(const Flashcard& frontCard, int i) const
{
	return frontCard.getLastUsages()[i] >= startTime_;
}