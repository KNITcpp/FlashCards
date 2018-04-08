#include "WriteToPDF.h"


#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler(HPDF_STATUS   error_no,
	HPDF_STATUS   detail_no,
	void         *user_data)
{
	printf("ERROR: error_no=%04X, detail_no=%u\n",
		(HPDF_UINT)error_no, (HPDF_UINT)detail_no);

	throw std::exception();
}

void DrawLayoutOfPage(HPDF_Page page)
{
	HPDF_REAL h, w;
	h = HPDF_Page_GetHeight(page);
	w = HPDF_Page_GetWidth(page);

	for (int i = 0; i < 16; i++)
	{
		HPDF_Page_SetLineWidth(page, 1);
		HPDF_Page_Rectangle(page, (i % 2) * w / 2, i / 2 * h / 8, w / 2, h / 8);
		HPDF_Page_Stroke(page);
	}
}

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

		for (int i = 0; i < 19; i++)
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

void PrintFlashCardsOnPage(std::vector<Flashcard> set, HPDF_Doc pdf, HPDF_Page page, int beginIndex, int endIndex)
{
	HPDF_Font def_font;
	HPDF_REAL text_width, height, width;
	int font_size;
	char text[20];

	font_size = 24;
	def_font = HPDF_GetFont(pdf, "Helvetica", NULL);
	HPDF_Page_SetFontAndSize(page, def_font, font_size);
	height = HPDF_Page_GetHeight(page);
	width = HPDF_Page_GetWidth(page);


	for (int i = beginIndex; i < endIndex; i++)
	{
		strcpy_s(text, set[i].getWord().c_str());

		text_width = HPDF_Page_TextWidth(page, text);
		HPDF_Page_BeginText(page);
		HPDF_Page_MoveTextPos(page, (width / 2 - text_width) / 2, height / 16 + height / 4 * (i % 8) / 2);
		HPDF_Page_ShowText(page, text);
		HPDF_Page_EndText(page);

		strcpy_s(text, set[i].getTranslation().c_str());

		text_width = HPDF_Page_TextWidth(page, text);
		HPDF_Page_BeginText(page);
		HPDF_Page_MoveTextPos(page, (width / 2 - text_width) / 2 + width / 2, height / 16 + height / 4 * (i % 8) / 2);
		HPDF_Page_ShowText(page, text);
		HPDF_Page_EndText(page);
	}
}

void ExportFlashcardsToPDF(std::vector<Flashcard> set, std::string fileName)
{
	HPDF_Doc  pdf;
	char fname[256];
	HPDF_Page * pages;
	int nSets, fCardsToFinish;

	strcpy_s(fname, fileName.c_str());
	strcat_s(fname, ".pdf");

	try
	{
		pdf = HPDF_New(error_handler, NULL);

		if (!pdf)
		{
			printf("error: cannot create PdfDoc object\n");
		}


		nSets = ceil(static_cast<double>(set.size()) / 8);
		fCardsToFinish = set.size();
		pages = new HPDF_Page[nSets];

		for (int i = 0; i < nSets; ++i)
		{
			pages[i] = HPDF_AddPage(pdf);

			DrawLayoutOfPage(pages[i]);

			if (fCardsToFinish < 8)
				PrintFlashCardsOnPage(set, pdf, pages[i], i * 8, set.size());
			else
				PrintFlashCardsOnPage(set, pdf, pages[i], i * 8, (i + 1) * 8);

			fCardsToFinish -= 8;
		}




		HPDF_SaveToFile(pdf, fname);

	}
	catch (...)
	{
		HPDF_Free(pdf);
	}

	HPDF_Free(pdf);
}
