#include "WriteToBinary.h"

WriteToBinary::WriteToBinary(std::string fname)
{
	fname += ".fcd";
	file_.open(fname.c_str(), std::ios::out | std::ios::binary);
}


void WriteToBinary::WriteFlashcard(Flashcard piece)
{
	int length, no;
	char  word[30];
	timeVector t = piece.getLastUsages();

	length = piece.getWord().length();
	strcpy_s(word, piece.getWord().c_str());

	file_.write((char*)&length, sizeof(int));
	file_.write((char*)word, sizeof(char)*(length+1));

	length = piece.getWord().length();
	strcpy_s(word, piece.getTranslation().c_str());

	file_.write((char*)&length, sizeof(int));
	file_.write((char*)word, sizeof(char)*(length + 1));

	no = piece.getGoodAnswers();
	file_.write((char*)&no, sizeof(int));

	no = piece.getBadAnswers();
	file_.write((char*)&no, sizeof(int));

	no = t.size();
	file_.write((char*)&no, sizeof(int));

	for (int i = 0; i < no; i++)
	{
		file_.write((char*)&t[i], sizeof(std::chrono::system_clock::time_point));
	}

}




void WriteToBinary::WriteSetToFile(std::vector<Flashcard> set)
{
	int nSets = set.size();
	file_.write((char*)&nSets, sizeof(int));
	
	for (int i = 0; i < set.size(); i++)
		WriteFlashcard(set[i]);

	file_.close();
}