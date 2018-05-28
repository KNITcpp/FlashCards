#include "ReadFromBinary.h"


ReadFromBinary::ReadFromBinary(std::string fname)
{
	fname += ".fcd";
	file_.open(fname.c_str());
}


void ReadFromBinary::ReadFlashcardFromBinary()
{
	char word[30], translation[30];
	int goodAnswers, badAnswers, length;
	std::chrono::system_clock::time_point temporary;
	timeVector t;

	file_.read((char*)&length, sizeof(int));
	file_.read((char*)&word, length+1);
	
	file_.read((char*)&length, sizeof(int));
	file_.read((char*)&translation, length+1);
	
	file_.read((char*)&goodAnswers, sizeof(int));
	file_.read((char*)&badAnswers, sizeof(int));
	
	Flashcard temp(word, translation, goodAnswers, badAnswers);

	file_.read((char*)&length, sizeof(int));
	for (int i = 0; i < length; i++)
	{
		file_.read((char*)&temporary, sizeof(std::chrono::system_clock::time_point));
		temp.addUsage(temporary);
	}

	readSet_.push_back(temp);
}


std::vector<Flashcard> ReadFromBinary::ReadSetFromBinary()
{
	file_.read((char*)&nSets_, sizeof(int));

	for (int i = 0; i < nSets_; i++)
		ReadFlashcardFromBinary();

	file_.close();

	return readSet_;
}
