#include "WebsiteFetcher.h"
#include <codecvt>
#include <exception>
#include <iostream>
#include <string>
#include <locale>
#include "curl/curl.h"





WebsiteFetcher::WebsiteFetcher(std::wstring link): link(link)
{
	curl_global_init(CURL_GLOBAL_ALL); //TODO: check if it's ok to call it every time new object is created (and curl_global_cleanup() in destructor also)

	getWebsite();
}

WebsiteFetcher::~WebsiteFetcher()
{
	curl_global_cleanup();
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;


  struct MemoryStruct *mem = (struct MemoryStruct*)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + sizeof(char)); //+sizeof(wchar_t) for null character at the tail of memory
  if(mem->memory == NULL)
    throw new std::exception("Not enough memory to save data fetched from web. ");
 
  memcpy(&(mem->memory[mem->size/sizeof(char)]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size/sizeof(char)] = 0; //mark tail of memory
 
  return realsize;
}

void WebsiteFetcher::convertToWstringAndSaveInVect(MemoryStruct chunk)
{
	std::string line;
	for (int i = 0; i < chunk.size / sizeof(wchar_t); ++i)
	{
		if (chunk.memory[i] == '\n') //end of line
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wstr = converter.from_bytes(line);

			fetchedCodeLines.push_back(wstr);
			line.clear();
		}
		else
			line.push_back(chunk.memory[i]);
	}
}

void WebsiteFetcher::setUpRequest(MemoryStruct& chunk, CURL* & handle)
{
	chunk.memory = (char*)malloc(1);
	chunk.size = 0; 
	handle=curl_easy_init(); 
	curl_easy_setopt(handle, CURLOPT_URL, "https://www.diki.pl//slownik-angielskiego?q=dog"); //TODO: refactor link
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // some servers don't like requests that are made without a user-agent field, so we provide one
}

void WebsiteFetcher::getWebsite()
{
	struct MemoryStruct chunk;
	CURL* handle;

	setUpRequest(chunk, handle);
	CURLcode result = curl_easy_perform(handle);

	if(result != CURLE_OK)
	{
		std::string errMsg= std::string("curl_easy_perform() failed: ") + std::string(curl_easy_strerror(result));
		throw CurlException(errMsg);
	}

	convertToWstringAndSaveInVect(chunk);
	free(chunk.memory);
 
	curl_easy_cleanup(handle);
}

std::wstring WebsiteFetcher::getLineOfCode(int index)
{
	if(getLinesQuantity()<=index || index<0)
		throw std::out_of_range("Called function WebsiteFetcher::getLineOfCode() with invalid index.");

	return fetchedCodeLines[index];
}

int WebsiteFetcher::getLinesQuantity() const
{
	return fetchedCodeLines.size();
}

