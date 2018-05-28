#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include "Flashcard.h"

class ReadFromBinary
{
private:
	std::ifstream file_;
	std::vector<Flashcard> readSet_;
	int nSets_;
	void ReadFlashcardFromBinary();
public:
	ReadFromBinary(std::string fname);
	std::vector<Flashcard> ReadSetFromBinary();
};

