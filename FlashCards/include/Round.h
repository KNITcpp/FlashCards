#pragma once
#include "Flashcard.h"
#include "StudyMode.h"
#include <vector>
#include  "CardPlayer.h"

class Flashcard;

class Round
{
public:
	Round(std::vector<Flashcard>& flashcards, StudyMode* studyMode);
	size_t cardsInRound() const noexcept;
	bool isEmpty() const noexcept;
	void setStartime();
	void play();
private:
	static const int cardReplayLimit = 3;
	std::vector<Flashcard>& flashcards_;
	StudyMode* studyMode_;
	std::vector <size_t> indexesInPlayOrder_;
	std::chrono::system_clock::time_point startTime_;
	CardPlayer cardPlayer_;
private:
	void checkResources() const;
	void preparePlayOrder();
	void reserveSpace();
	void fillPlayOrder();
	void playAllCards();
	bool isCardToPlay() const noexcept;
	void playCard();
	void proceedBadAnswer(Flashcard& frontCard);
	void proceedCorrectAnswer(Flashcard& frontCard);
	void eraseFrontCardFromPlay();
	void insertFrontcardAtNewPosition();
	size_t countOccurencesInRound(const Flashcard& frontCard) const noexcept;
	bool isValidToPlay(Flashcard& frontCard);
	bool wasUsedInThisRound(const Flashcard& frontCard, int i) const;
	static void addBadAnswer(Flashcard& frontCard);
	static void addGoodAnswer(Flashcard& frontCard);
	static std::chrono::system_clock::time_point getCurrentTime() noexcept;
};