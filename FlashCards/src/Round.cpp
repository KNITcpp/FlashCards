#include "Round.h"


Round::Round(std::vector<Flashcard>& flashcards, StudyMode* studyMode) :
	flashcards_(flashcards),
	studyMode_(studyMode)
{
	checkResources();
}

void Round::checkResources() const
{
	if (studyMode_ == nullptr)
		throw std::logic_error("Round::play() : studyMode is nullptr");
}


size_t Round::cardsToGo() const
{
	return flashcards_.size();
}


bool Round::isEmpty() const
{
	return flashcards_.empty();
}


void Round::addFlashcards(std::vector<Flashcard>& flashcards)
{
	flashcards_.insert(flashcards_.end(), flashcards.begin(), flashcards.end());
}


void Round::play()
{
	for (auto& i : flashcards_)
	{
		updateCurrentTime();
		playCard(i);
	}
}


void Round::updateCurrentTime()
{
	currentTime_ = std::chrono::system_clock::now();
}


void Round::playCard(std::vector<Flashcard>::value_type& flashcard)
{
	flashcard.addUsage(currentTime_);
	studyMode_->performFlashcard(flashcard);
}