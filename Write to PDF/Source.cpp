#include <iostream>
#include "WriteToPDF.h"
#include "Flashcard.h"

int main()
{
	std::vector<Flashcard> set = CreateDefaultSet(22);

	ExportFlashcardsToPDF(set, "Zestaw");

	return 0;
}