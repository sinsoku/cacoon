#include "stdafx.h"

#include "CacooApi.h"
#include "CacooComment.hpp"

TEST(CacooComment, init)
{
	char rawXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<comment>"
		"  <user>"
		"    <name>yoko</name>"
		"    <nickname>Yoko</nickname>"
		"    <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"  </user>"
		"  <content>comment 1</content>"
		"  <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"  <updated>Mon, 10 Aug 2009 17:00:00 +0900</updated>"
		"</comment>";
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(rawXmlData);
	CacooComment actual( doc->RootElement() );

	CacooUser user = actual.getUser();
	EXPECT_EQ("yoko", user.getName() );
	EXPECT_EQ("Yoko", user.getNickName() );
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", user.getImageUrl() );
	EXPECT_EQ("comment 1", actual.getContent() );
	time_t t = actual.getCreated();
	struct tm* cal = localtime( &t );
	EXPECT_EQ(2009, cal->tm_year + 1900);
	EXPECT_EQ(8,    cal->tm_mon + 1);
	EXPECT_EQ(10,   cal->tm_mday);
	EXPECT_EQ(17,   cal->tm_hour);
	EXPECT_EQ(0, cal->tm_min);
	EXPECT_EQ(0, cal->tm_sec);

	time_t t2 = actual.getCreated();
	struct tm* cal2 = localtime( &t2 );
	EXPECT_EQ(2009, cal2->tm_year + 1900);
	EXPECT_EQ(8,    cal2->tm_mon + 1);
	EXPECT_EQ(10,   cal2->tm_mday);
	EXPECT_EQ(17,   cal2->tm_hour);
	EXPECT_EQ(0,    cal2->tm_min);
	EXPECT_EQ(0,    cal2->tm_sec);
}

TEST(CacooComment, parseDate)
{
	std::string strdate = "Mon, 10 Aug 2009 17:00:00 +0900";
	std::vector<std::string> date;
	CacooComment::parseDate(date, strdate);

	ASSERT_EQ(8, date.size());
	EXPECT_EQ("Mon", date[0]);
	EXPECT_EQ("10", date[1]);
	EXPECT_EQ("Aug", date[2]);
	EXPECT_EQ("2009", date[3]);
	EXPECT_EQ("17", date[4]);
	EXPECT_EQ("00", date[5]);
	EXPECT_EQ("00", date[6]);
	EXPECT_EQ("+0900", date[7]);
}

TEST(CacooComment, timeFromString)
{
	std::string strdate = "Mon, 10 Aug 2009 17:00:00 +0900";
	EXPECT_EQ(1249891200, CacooComment::timeFromString(strdate) );
}
