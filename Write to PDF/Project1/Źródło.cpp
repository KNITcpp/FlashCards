#include "WriteToPDF.h"

int main(int argc, char **argv)
{
	//default usage of functions
		srand(time(NULL));

		
		std::vector<Flashcard> set = CreateDefaultSet(26);

		ExportFlashcardsToPDF(set, "Zestaw");






	return 0;
}