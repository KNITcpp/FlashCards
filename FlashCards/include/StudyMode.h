#pragma once

class Flashcard;

class StudyMode
{
public:
	virtual ~StudyMode() = default;
	virtual bool performFlashcard(const Flashcard& flashcard) = 0;
};