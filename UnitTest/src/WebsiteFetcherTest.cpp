#include "gtest/gtest.h"
#include "WebsiteFetcher.h"
class WebsiteFetcherTest: public ::testing::Test
{
protected:
	WebsiteFetcher existingWebsite;
	WebsiteFetcherTest(): existingWebsite(L"http://www.example.com"){}
};


TEST_F(WebsiteFetcherTest, fetchingExistingWebsite)
{
	ASSERT_NE(existingWebsite.getLinesQuantity(), 0);
}

TEST_F(WebsiteFetcherTest, gettingNotExistingLine)
{
	const int NOT_EXISTING_LINE=existingWebsite.getLinesQuantity()+10;
	ASSERT_THROW(existingWebsite.getLineOfCode(NOT_EXISTING_LINE), std::out_of_range);
}

TEST_F(WebsiteFetcherTest, gettingExistingLines)
{
	for(int i=0; i<existingWebsite.getLinesQuantity()-2; ++i)
		ASSERT_NO_THROW(existingWebsite.getLineOfCode(i), std::out_of_range);	

}





//TODO: getting not existing site