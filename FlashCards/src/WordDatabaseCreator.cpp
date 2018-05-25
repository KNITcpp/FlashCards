#include <vector>
#include "WordDatabaseCreator.h"
#include "StringWordSplitter.h"


std::unordered_map<std::wstring/*word*/, int /*occurences*/> WordDatabaseCreator::getWords()
{
	return wordDatabase;
}

void WordDatabaseCreator::process(const std::wstring& str)
{

	StringWordSplitter splitter(str);

	for(int i=0; i<splitter.size(); ++i)
	{
		std::wstring currentWord=splitter[i];

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

	//TODO: check if it doesn't append endl char also
}


//TODO: test for creation of database based on string like "something, something" and check if something won't be duplicated twice: once with comma, once without
