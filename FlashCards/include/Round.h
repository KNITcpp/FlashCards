#pragma once
#include "Flashcard.h"
#include "StudyMode.h"
#include <vector>


class Flashcard;

class Round
{
public:
	Round(std::vector<Flashcard>& flashcards, StudyMode* studyMode);
	size_t cardsToGo() const;
	bool isEmpty() const;
	void addFlashcards(std::vector<Flashcard>& flashcards);
	void play();
private:
	std::vector<Flashcard>& flashcards_;
	StudyMode* studyMode_;
	std::chrono::system_clock::time_point currentTime_;
private:
	void checkResources() const;
	void playCard(std::vector<Flashcard>::value_type& flashcard);
	void updateCurrentTime();
};