#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "Flashcard.h"

class WriteToBinary
{
private:
	std::ofstream file_;
	void WriteFlashcard(Flashcard piece);
public:
	WriteToBinary(std::string fname);
	void WriteSetToFile(std::vector<Flashcard> set);
};
