#pragma once
#include <unordered_map>

struct WordWithFrequency;

class WordDatabaseCreator
{
	std::unordered_map<std::wstring/*word*/, int /*occurences*/> wordDatabase;
	void deletePunctuationMarks(std::wstring& str);
public:
	std::unordered_map<std::wstring/*word*/, int /*occurences*/> getWords();
	void process(const std::wstring& str);

};

class WordWithFrequency
{
public:
	std::wstring word;
	int frequency=0;
};
