#include "Session.h"


Session::Session(std::vector<Flashcard>& flashcards, StudyMode* studyMode)
	: flashcards_(flashcards),
	studyMode_(studyMode),
	roundLength_(1)
{

}


void Session::play()
{
	Round round(flashcards_, studyMode_);
	round.play();
}


size_t Session::getNumOfRounds() const
{
	return flashcards_.size()/roundLength_;
}


void Session::setRoundLength(const size_t roundLength)
{
	roundLength_ = roundLength;
}
