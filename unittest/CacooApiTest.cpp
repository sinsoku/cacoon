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
