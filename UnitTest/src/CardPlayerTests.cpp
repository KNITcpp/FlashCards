#include <gtest/gtest.h>
#include "CardPlayer.h"
#include "Flashcard.h"
#include "StudyMode.h"

class MockDoNothingStudyMode : public StudyMode
{
public:
	bool performFlashcard(const Flashcard& flashcard) override
	{
		wasInvoked_ = true;
		return true;
	}
	bool wasInvoked() const { return wasInvoked_; }
private:
	bool wasInvoked_ = false;
};

TEST(ACardPlayer, PlaysTheCard)
{
	Flashcard card("word", "translation");
	MockDoNothingStudyMode mode;
	CardPlayer cardPlayer;

	cardPlayer.play(card,&mode);

	ASSERT_GT(card.getLastUsages().size(), 0);

}