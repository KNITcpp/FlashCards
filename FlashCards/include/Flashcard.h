#pragma once
#include <string>
#include <vector>
#include <chrono>

using timeVector = std::vector<std::chrono::system_clock::time_point>;

class Flashcard
{
public:
	Flashcard(const std::string& word, const std::string& translation,
		const int goodAnswers = 0, const int badAnswers = 0) noexcept;
	Flashcard(const Flashcard& rhs) = default;
	Flashcard(Flashcard&& rhs) = default;
	virtual ~Flashcard() = default;
	Flashcard& operator=(Flashcard&& other) = default;
	Flashcard& operator=(const Flashcard& rhs) = default;

	std::string getWord() const noexcept;
	std::string getTranslation() const noexcept;
	int getGoodAnswers() const noexcept;
	int getBadAnswers() const noexcept;
	timeVector getLastUsages() const noexcept;
	void addGoodAnswer() noexcept;
	void addBadAnswer() noexcept;
	void addUsage(const std::chrono::system_clock::time_point& usageDate = std::chrono::system_clock::now());
private:
	std::string word_;
	std::string translation_;
	int goodAnswers_;
	int badAnswers_;
	timeVector lastUsages_;
};