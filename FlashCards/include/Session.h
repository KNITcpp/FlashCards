#pragma once
#include "Round.h"


class Session
{
public:
	Session(std::vector<Flashcard>& flashcards, StudyMode* studyMode);
	void play();
	size_t getNumOfRounds() const;
	void setRoundLength(size_t roundLength);
private:
	std::vector<Flashcard>& flashcards_;
	StudyMode* studyMode_;
	size_t roundLength_;
};
