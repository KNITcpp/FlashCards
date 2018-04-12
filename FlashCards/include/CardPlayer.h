#pragma once
#include "Flashcard.h"
#include "StudyMode.h"

class CardPlayer
{
public:
	CardPlayer();
	void play(Flashcard& flashcard, StudyMode* studyMode);
	bool isAnswerCorrect() const;
private:
	StudyMode* studyMode_;
	bool isAnswerCorrect_;
private:
	bool runStudyMode(Flashcard& flashcard);
};
