#pragma once
#include <string>
#include <vector>

typedef void CURL;

struct MemoryStruct 
{
  char *memory;
  size_t size;
};

class WebsiteFetcher
{
	std::vector<std::wstring> fetchedCodeLines;
	std::string link;
	void convertToWstringAndSaveInVect(MemoryStruct chunk);
	void setUpRequest(MemoryStruct& chunk, CURL* & handle);
	void getWebsite();

public:
	explicit WebsiteFetcher(std::string link); // throws std::exception;
	~WebsiteFetcher();
	std::wstring getLineOfCode(int index);
	int getLinesQuantity() const;

};

class CurlException: public std::exception
{
	std::string whatHappened;
public:
	CurlException(std::string whatHappened): whatHappened(whatHappened)
	{
	}

	char const* what() const override
	{
		return whatHappened.c_str();
	}

};
