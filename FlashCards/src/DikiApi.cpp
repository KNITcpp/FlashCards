#include "DikiApi.h"
#include <regex>
#include "WebsiteFetcher.h"

std::vector<TransWithExamp> DikiApi::getTranslation(std::wstring toTranslate)
{
	std::wstring singleTranslation;
	std::vector<TransWithExamp> translation;
	std::vector<Example> example;
	std::wstring line; 

	std::string toTranslateWithoutPolishLetters=convertPolishLetters(toTranslate);
	std::string link=API_LINK+toTranslateWithoutPolishLetters;

	WebsiteFetcher websiteFetcher(link);

	bool readyToPush=false;

	for(int i=0; i<websiteFetcher.getLinesQuantity(); ++i)
	{
		line = websiteFetcher.getLineOfCode(i);

		if(hasReachedTheEnd(line))
			break;

		if(hasFoundLinePrecedingTranslation(line))
		{
			if(readyToPush==true)
			{
				translation.emplace_back(toTranslate, singleTranslation, example);

				example.resize(0);
				readyToPush=false;
			}

			line=websiteFetcher.getLineOfCode(i+1);
			singleTranslation=convertTranslationLine(line);
			readyToPush=true;
			++i;
		}
		else if(hasFoundLinePrecedingExample(line))
		{
			line=websiteFetcher.getLineOfCode(i+1);
			std::wstring secondLine=websiteFetcher.getLineOfCode(i+2);
			Example singleExample=convertExampleLine(line, secondLine);
			example.push_back(singleExample);
			i+=2;
		}
	}

	if(readyToPush==true)
			translation.emplace_back(toTranslate, singleTranslation, example);

	return translation;
}

char DikiApi::convertPolishToAscii(const wchar_t wideLetter)
{
	switch(wideLetter)
	{
		case L'ę':
			return 'e';
		case L'ó':
			return 'o';
		case L'ą':
			return 'a';
		case L'ś':
			return 's';
		case L'ł':
			return 'l';
		case L'ż':
			return 'z';
		case L'ź':
			return 'z';
		case L'ć':
			return 'c';
		case L'ń':
			return 'n';
	}

	if(wideLetter<0 || wideLetter > 127)
		throw std::exception("Invalid link. ");

	return static_cast<char>(wideLetter);
}

bool DikiApi::hasReachedTheEnd(std::wstring line)
{
	const std::wstring ENDING_LINE=L"Powiązane zwroty";
	return line.find(ENDING_LINE)!=std::string::npos;
}

bool DikiApi::hasFoundLinePrecedingTranslation(std::wstring line)
{
	std::wstring linePrecedingTranslation(LR"_DELIM_([[:space:]]*<li id="meaning[[:digit:]]+_id" class="meaning[[:digit:]]+" >)_DELIM_");
	return std::regex_match(line, std::wregex(linePrecedingTranslation));
}

std::wstring DikiApi::convertTranslationLine(std::wstring line)
{
	std::wstring emptyStr(L"");

	std::wstring spareSpaces = std::wstring(L"[[:space:]]{2,}");
	line = std::regex_replace(line, std::wregex(spareSpaces), emptyStr);

	std::wstring htmlTag = std::wstring(L"<[[:print:]]+?>");
	line = std::regex_replace(line, std::wregex(htmlTag), emptyStr);
	
	std::wstring end=std::wstring(L"<[[:print:]]+\\(this,");
	line = std::regex_replace(line, std::wregex(end), emptyStr);

	return line;
}

bool DikiApi::hasFoundLinePrecedingExample(std::wstring line)
{
	return line.find(LR"(<div class="exampleSentence">)")!=std::wstring::npos;
}

Example DikiApi::convertExampleLine(const std::wstring& firstLine, const std::wstring& secondLine)
{
	Example example;
	example.sentence=extractSentence(firstLine);
	example.sentenceTranslation=extractTranslation(secondLine);
	
	return example;
}

std::wstring DikiApi::extractSentence(const std::wstring& line)
{
	// cuts out sentence from line formated this way: [spaces]sentence<span...
	int lengthOfSentence=line.find(L"<span") - line.find_first_not_of(' ');
	std::wstring sentence=line.substr(line.find_first_not_of(' '), lengthOfSentence);

	fixProblemWithSingleQuotationMark(sentence);
	deleteSpareSpaces(sentence);
	return sentence;
}

void DikiApi::fixProblemWithSingleQuotationMark(std::wstring &sentence)
{
	const std::wstring TO_REPLACE=L"&#039;";
	size_t pos;
	while((pos=sentence.find(TO_REPLACE))!=std::wstring::npos)
		sentence.replace(pos, TO_REPLACE.length(), L"'");
}

void DikiApi::deleteSpareSpaces(std::wstring& str)
{
	std::wstring spareSpaces(L"[[:space:]]{2,}");
	std::wstring emptyStr(L"");
	str=std::regex_replace(str, std::wregex(spareSpaces), emptyStr);
}

std::wstring DikiApi::extractTranslation(const std::wstring& line)
{
	// cuts out sentence from line formated this way: [spaces](sentenceTranslation)
	int lengthOfTranslation=line.find(')') - line.find_first_not_of(' ')-1;//-1 to exclude begining '('
	std::wstring translation=line.substr(line.find_first_not_of(' ')+1, lengthOfTranslation); //+1 to skip begining '('

	return translation;
}

std::string DikiApi::convertPolishLetters(const std::wstring& strWithPolishLetters)
{
	std::string withoutPolish;
	for(int i=0; i<strWithPolishLetters.size();++i)
	{
		char asciiLetter=convertPolishToAscii(strWithPolishLetters[i]);
		withoutPolish+=asciiLetter;
	}
	return withoutPolish;
}



