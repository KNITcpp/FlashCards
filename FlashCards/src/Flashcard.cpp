#include "Flashcard.h"


Flashcard::Flashcard(std::string word, std::string translation, const int goodAnswers, const int badAnswers) noexcept :
	word_(word),
	translation_(translation),
	goodAnswers_(goodAnswers),
	badAnswers_(badAnswers),
	lastUsages_()
{

}

Flashcard::Flashcard(const Flashcard& rhs) noexcept :
	word_(rhs.word_),
	translation_(rhs.translation_),
	goodAnswers_(0),
	badAnswers_(0),
	lastUsages_()
{
	
}

Flashcard::Flashcard(Flashcard&& rhs) noexcept
	: word_(std::move(rhs.word_)),
	translation_(std::move(rhs.translation_)),
	goodAnswers_(rhs.goodAnswers_),
	badAnswers_(rhs.badAnswers_),
	lastUsages_(std::move(rhs.lastUsages_))
{

}

std::string Flashcard::getWord() const noexcept
{
	return word_;
}


std::string Flashcard::getTranslation() const noexcept
{
	return translation_;
}

int Flashcard::getGoodAnswers() const noexcept
{
	return goodAnswers_;
}

int Flashcard::getBadAnswers() const noexcept
{
	return badAnswers_;
}

timeVector Flashcard::getLastUsages() const noexcept
{
	return lastUsages_;
}

void Flashcard::addGoodAnswer() noexcept
{
	++goodAnswers_;
}

void Flashcard::addBadAnswer() noexcept
{
	++badAnswers_;
}
