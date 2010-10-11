#include "stdafx.h"
#include "CacooApi.h"
#include "MockServer.h"

TEST(CacooApi, parseXml_shared)
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<account>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</account>";
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);
}

TEST(CacooApi, diagrams)
{
}

TEST(CacooApi, diagram)
{
	boost::shared_ptr<CacooServer> mock(new MockServer());
	CacooApi api(mock);
	CacooDiagram diagram = api.Diagram("00e77f4dc9973517");

	time_t t = diagram.getCreated();
	struct tm* cal = localtime( &t );
	EXPECT_EQ(2009, cal->tm_year + 1900);
	EXPECT_EQ(8,    cal->tm_mon + 1);
	EXPECT_EQ(10,   cal->tm_mday);
	EXPECT_EQ(17,   cal->tm_hour);
	EXPECT_EQ(0, cal->tm_min);
	EXPECT_EQ(0, cal->tm_sec);

	time_t t2 = diagram.getUpdated();
	struct tm* cal2 = localtime( &t2 );
	EXPECT_EQ(2009, cal2->tm_year + 1900);
	EXPECT_EQ(8,    cal2->tm_mon + 1);
	EXPECT_EQ(10,   cal2->tm_mday);
	EXPECT_EQ(17,   cal2->tm_hour);
	EXPECT_EQ(0,    cal2->tm_min);
	EXPECT_EQ(0,    cal2->tm_sec);
}

TEST(CacooApi, users) 
{
	boost::shared_ptr<CacooServer> mock(new MockServer());
	CacooApi api(mock);
	CacooUser user = api.Users("yoko");

	EXPECT_EQ("yoko", user.getName() );
	EXPECT_EQ("Yoko", user.getNickName() );
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", user.getImageUrl() );
}

TEST(CacooApi, image)
{
}

TEST(CacooApi, chatmessages)
{
}

TEST(CacooApi, folders)
{
}

TEST(CacooApi, account)
{
	boost::shared_ptr<CacooServer> mock(new MockServer());
	CacooApi api(mock);
	CacooUser user = api.Account();

	EXPECT_EQ("yoko", user.getName() );
	EXPECT_EQ("Yoko", user.getNickName() );
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", user.getImageUrl() );
}
