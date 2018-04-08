#pragma once
#include <string>
#include <fstream>
#include <vector>

class WebsiteFetcher
{

	std::wstring fetchedFilePath;
	std::wfstream fileHandler;
	std::vector<std::wstring> codeLines;
	std::vector<std::wstring> fetchedCodeLines;
	std::wstring link;
	std::wstring downloadWebsite(const std::wstring& link);
	void loadFileIntoMemory();
	void closeAndDeleteFile();
	void downloadAndOpenFile(std::wstring link);
	void deleteFile();
	void getWebsite();

public:
	explicit WebsiteFetcher(std::wstring link); // throws std::exception;
	~WebsiteFetcher();
	std::wstring getLineOfCode(int index);
	int getLinesQuantity() const;

};

//TODO: translation for word that doesn't exist