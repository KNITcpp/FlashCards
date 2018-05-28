#include <vector>
#include "WordDatabaseCreator.h"
#include "StringWordSplitter.h"
#include <algorithm>
#include <iterator>
#include <regex>


void WordDatabaseCreator::deletePunctuationMarks(std::wstring& str)
{
	std::wstring emptyStr=L"";
	std::wstring punctuationMarks = std::wstring(L"[[:punct:]]*");
	str = std::regex_replace(str, std::wregex(punctuationMarks), emptyStr);
}

std::unordered_map<std::wstring/*word*/, int /*occurences*/> WordDatabaseCreator::getWords()
{
	return wordDatabase;
}

void WordDatabaseCreator::process(const std::wstring& str)
{
	std::wstring toLowerStr;
	std::transform(str.begin(), str.end(), std::insert_iterator<std::wstring>(toLowerStr, toLowerStr.begin()), tolower);
	StringWordSplitter splitter(toLowerStr);

	for(int i=0; i<splitter.size(); ++i)
	{
		std::wstring currentWord=splitter[i];
		deletePunctuationMarks(currentWord);

		auto iterToInsertedElem=wordDatabase.find(currentWord);
		if(iterToInsertedElem == wordDatabase.end()) //if word not exists insert it
		{
			std::pair<std::wstring, int> elemToInsert(currentWord, 1);
			wordDatabase.insert(elemToInsert);
		}
		else // if it does, increment occurences
		{
			++(*iterToInsertedElem).second;
		}
	}
}
