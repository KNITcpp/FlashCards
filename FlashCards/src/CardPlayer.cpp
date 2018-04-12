#include "CardPlayer.h"


CardPlayer::CardPlayer()
	: isAnswerCorrect_(false)
{

}


void CardPlayer::play(Flashcard& flashcard, StudyMode* studyMode)
{
	studyMode_ = studyMode;
	flashcard.addUsage();
	isAnswerCorrect_ = runStudyMode(flashcard);
}

bool CardPlayer::runStudyMode(Flashcard& flashcard)
{
	return studyMode_->performFlashcard(flashcard);
}

bool CardPlayer::isAnswerCorrect() const //TODO zabezpieczyc przed wywolaniem przed play
{
	return  isAnswerCorrect_;
}
