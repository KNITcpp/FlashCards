#include "gtest/gtest.h"
#include "WebsiteFetcher.h"
class WebsiteFetcherTest: public ::testing::Test
{
protected:
	WebsiteFetcher existingWebsite;
	WebsiteFetcherTest(): existingWebsite("http://www.example.com"){}
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

TEST(FetchingWebsiteWithoutPrefix, AlwaysSuccedes)
{
	WebsiteFetcher w1("www.google.com");
	EXPECT_NE(w1.getLinesQuantity(), 0);

	WebsiteFetcher w2("google.com");
	EXPECT_NE(w1.getLinesQuantity(), 0);
}

TEST(FetchingAFewWebsitesAtOneSession, AlwaysSuccedes)
{
	ASSERT_NO_THROW(
		WebsiteFetcher w1("www.google.com");
		WebsiteFetcher w2("http://www.example.com");
		WebsiteFetcher w3("https://ebay.com");
	);

	WebsiteFetcher w1("www.google.com");
	EXPECT_NE(w1.getLinesQuantity(),0);
	WebsiteFetcher w2("http://www.example.com");
	EXPECT_NE(w2.getLinesQuantity(),0);
	WebsiteFetcher w3("https://www.ebay.com");
	EXPECT_NE(w3.getLinesQuantity(),0);
}



//TODO: getting not existing site