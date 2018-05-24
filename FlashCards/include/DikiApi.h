#pragma once
#include <string>
#include <vector>
#include "WebsiteFetcher.h"

struct Example
{
	std::wstring sentence;
	std::wstring sentenceTranslation;

	Example()=default;
	Example(const std::wstring& sentence, const std::wstring& translation)
		: sentence(sentence),
		  sentenceTranslation(translation)
	{
	}
};

struct TransWithExamp
{
	std::wstring word;
	std::wstring translation;
	std::vector<Example> example;

	TransWithExamp()=default;
	TransWithExamp(std::wstring word, std::wstring translation, std::vector<Example> example)
		: word(word), translation(translation), example(example) {}
};

class DikiApi
{
	const std::string API_LINK = "https://www.diki.pl/slownik-angielskiego?q=";
	std::wstring convertTranslationLine(std::wstring line);

	bool hasFoundLinePrecedingTranslation(std::wstring line);
	bool hasReachedTheEnd(std::wstring line);
	void deleteSpareSpaces(std::wstring& str);
	Example convertExampleLine(const std::wstring& firstLine, const std::wstring& secondLine);
	bool hasFoundLinePrecedingExample(std::wstring line);
	void fixProblemWithSingleQuotationMark(std::wstring& sentence);
	std::wstring extractSentence(const std::wstring& firstLine);
	std::wstring extractTranslation(const std::wstring& secondLine);
	std::string convertPolishLetters(const std::wstring& strWithPolishLetters);
	char convertPolishToAscii(const wchar_t wideLetter);
	bool hasFoundLinePrecedingWordToTranslate(const std::wstring& line);
	bool hasFoundLineFollowingWordToTranslate(const std::wstring& line);
	void deleteHtmlTags(std::wstring& text);
	void deleteSpareStars(std::wstring& text);
public:
	std::vector<TransWithExamp> getTranslation(std::wstring toTranslate);

};



