#include "Flashcard.h"
#include <chrono>


Flashcard::Flashcard(const std::string& word, const std::string& translation, const int goodAnswers, const int badAnswers) noexcept :
	word_(word),
	translation_(translation),
	goodAnswers_(goodAnswers),
	badAnswers_(badAnswers),
	lastUsages_()
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

void Flashcard::addUsage(const std::chrono::system_clock::time_point& usageDate)
{
	lastUsages_.push_back(usageDate);
}