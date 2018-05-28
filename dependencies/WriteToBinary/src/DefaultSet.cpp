#include "DefaultSet.h"

std::vector<Flashcard> CreateDefaultSet(int no)
{
	std::vector<Flashcard> set;
	std::string name;
	std::string trans;
	char c;


	for (int i = 0; i < no; i++)
	{
		name = "";
		trans = "";

		for (int i = 0; i < 9; i++)
		{
			c = rand() % 26 + 97;
			name = name + c;
			c = rand() % 26 + 97;
			trans = trans + c;
		}

		Flashcard temp(name, trans);
		set.push_back(temp);
	}
	return set;
}