#include "stdafx.h"
#include "CacooApi.h"
#include "MockServer.h"

TEST(CacooApi, parseXml)
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<account>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</account>";
	std::map<std::string, std::string> xmldata;
	CacooApi::parseXml(xmldata, resXmlData);
	
	EXPECT_EQ("yoko", xmldata["name"]);
	EXPECT_EQ("Yoko", xmldata["nickname"]);
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", xmldata["imageUrl"]);
}

TEST(CacooApi, paserUser)
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<account>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</account>";
	CacooUser user = CacooApi::parseUser(resXmlData);

	EXPECT_EQ("yoko", user.name);
	EXPECT_EQ("Yoko", user.nickname);
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl);
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

	EXPECT_EQ("yoko", user.name);
	EXPECT_EQ("Yoko", user.nickname);
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl);
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

	EXPECT_EQ("yoko", user.name);
	EXPECT_EQ("Yoko", user.nickname);
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl);
}
