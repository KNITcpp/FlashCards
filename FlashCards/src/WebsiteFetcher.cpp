#include "WebsiteFetcher.h"
#include <codecvt>
#include "curl/curl.h"
#include <exception>


std::wstring WebsiteFetcher::downloadWebsite(const std::wstring& link)
{
	//TODO: implement
	return L"additional\\dog.html";
}

void WebsiteFetcher::loadFileIntoMemory()
{
	int i=0;
	std::wstring line;
	while(getline(fileHandler, line))
		codeLines.push_back(line);
}

void WebsiteFetcher::closeAndDeleteFile()
{
	if(fileHandler.is_open())
		fileHandler.close();
	deleteFile();
}

void WebsiteFetcher::downloadAndOpenFile(std::wstring link)
{
	fetchedFilePath=downloadWebsite(link);
	fileHandler.open(fetchedFilePath, std::wfstream::in);

	if(fileHandler.good()==false)
	throw std::exception("Invalid link. ");

	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	fileHandler.imbue(utf8_locale);
}

WebsiteFetcher::WebsiteFetcher(std::wstring link): link(link)
{
	curl_global_init(CURL_GLOBAL_ALL); //TODO: check if it's ok to call it every time new object is created (and curl_global_cleanup() in destructor also)

	downloadAndOpenFile(link);
	loadFileIntoMemory();
	closeAndDeleteFile();

	getWebsite();
}

WebsiteFetcher::~WebsiteFetcher()
{
	curl_global_cleanup();
}

void WebsiteFetcher::deleteFile()
{
	//TODO: implement
}

struct MemoryStruct 
{
  wchar_t *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct*)userp;
 
  mem->memory = (wchar_t*)realloc(mem->memory, mem->size + realsize + 1); //+1 for null character at the tail of memory
  if(mem->memory == NULL)
    throw new std::exception("Not enough memory to save data fetched from web. ");
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0; //mark tail of memory
 
  return realsize;
}

void WebsiteFetcher::getWebsite()
{
	struct MemoryStruct chunk;
	chunk.memory = (wchar_t*)malloc(1);
	chunk.size = 0;   
	CURL* handle;
	handle=curl_easy_init(); 

	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); //TODO: probably to delete
	curl_easy_setopt(handle, CURLOPT_URL, "https://diki.pl"); //TODO: refactor link
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // some servers don't like requests that are made without a user-agent field, so we provide one
  
	CURLcode result = curl_easy_perform(handle);
 
	if(result != CURLE_OK)
	{
		std::string* errMsg=new std::string("curl_easy_perform() failed: ");
		(*errMsg)+=curl_easy_strerror(result);
		throw std::exception(errMsg->c_str()); //TODO: memory leak, change exception
	}
	else
	{
		std::wstring line;
		for(int i=0; i<chunk.size; ++i)
		{
			if(chunk.memory[i]==0) //end of line
			{
				fetchedCodeLines.push_back(line);
			}
			else
				line.push_back(chunk.memory[i]);
		}
	}
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(handle);
 
  free(chunk.memory);
}



std::wstring WebsiteFetcher::getLineOfCode(int index)
{
	if(getLinesQuantity()<=index || index<0)
		throw std::out_of_range("Called function WebsiteFetcher::getLineOfCode() with invalid index.");

	return codeLines[index];
}

int WebsiteFetcher::getLinesQuantity() const
{
	return codeLines.size();
}

