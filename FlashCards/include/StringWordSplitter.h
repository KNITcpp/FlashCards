#pragma once
#include <string>
#include <vector>

class StringWordSplitter
{
	std::vector<std::wstring> words;
public:
	StringWordSplitter(std::wstring strToBeSplitted);
	size_t size() {return words.size();}
	std::wstring& operator[](size_t index) {return words[index];}
};
