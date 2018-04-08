#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <exception>
#include <vector>
#include <ctime>
#include <cmath>
#include "hpdf.h"
#include "Flashcard.h"

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler(HPDF_STATUS   error_no,
	HPDF_STATUS   detail_no,
	void         *user_data);
/*
 * Param in: page of document.
 * Function draws rectangles for each Flascards
 */
void DrawLayoutOfPage(HPDF_Page page);
/*
 * Param in: number of wanted flashcards
 * Function creates set of flashcards with random letters
 */
std::vector<Flashcard> CreateDefaultSet(int no);
/*
 * Param in: set of flashcards, pdf document, page of document, begin and end index of set to write
 * Function writes words in prepared rectangles
 */
void PrintFlashCardsOnPage(std::vector<Flashcard> set, HPDF_Doc pdf, HPDF_Page page, int beginIndex, int endIndex);
/*
 * Param in: set of flashcards, name of pdf document to write to
 * This is the main function to use if you want to write set to pdf
 */
void ExportFlashcardsToPDF(std::vector<Flashcard> set, std::string fileName);
