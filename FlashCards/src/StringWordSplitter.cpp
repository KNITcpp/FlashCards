
#include "StringWordSplitter.h"
#include <string>
#include <vector>

StringWordSplitter::StringWordSplitter(std::wstring strToBeSplitted)
{
	std::wstring singleWord;

	for(int i=0; i<strToBeSplitted.length(); ++i)
	{
		if(strToBeSplitted[i] == L' ')
		{
			if(singleWord.size()!=0)
			{
				words.push_back(singleWord);
				singleWord.clear();
			}
		}
		else
			singleWord.push_back(strToBeSplitted[i]);
	}

	if(singleWord.size()!=0) //something left to push after loop
		words.push_back(singleWord);
}
