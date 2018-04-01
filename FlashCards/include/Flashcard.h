#pragma once
#include <string>
#include <vector>
#include <chrono>

using timeVector = std::vector<std::chrono::system_clock::time_point>;

class Flashcard
{
public:
	Flashcard(const std::string& word, const std::string& translation, const int goodAnswers = 0, const int badAnswers = 0) noexcept;
	Flashcard(const Flashcard& rhs) noexcept;
	Flashcard(Flashcard&& rhs) noexcept;
	virtual ~Flashcard() = default;
	Flashcard& operator=(Flashcard&& other) = delete;
	Flashcard& operator=(const Flashcard& rhs) = delete;

	std::string getWord() const noexcept;
	std::string getTranslation() const noexcept;
	int getGoodAnswers() const noexcept;
	int getBadAnswers() const noexcept;
	timeVector getLastUsages() const noexcept;
	void addGoodAnswer() noexcept;
	void addBadAnswer() noexcept;
	void addUsage(const std::chrono::system_clock::time_point& usageDate);
private:
	const std::string word_;
	const std::string translation_;
	int goodAnswers_;
	int badAnswers_;
	timeVector lastUsages_;
};