#include "stdafx.h"
#include "CacooApi.h"
#include "MockServer.h"

TEST(CacooApi, parse)
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<account>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</account>";
	std::map<std::string, std::string> xmldata;
	xmldata = CacooApi::parseXml(resXmlData);
	
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

	EXPECT_STREQ("yoko", user.name.c_str());
	EXPECT_STREQ("Yoko", user.nickname.c_str());
	EXPECT_STREQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl.c_str());
}

TEST(CacooApi, users) 
{
	MockServer* mock = new MockServer();
	CacooApi api;
	api.setServer(mock);
	CacooUser user = api.Users("yoko");

	EXPECT_STREQ("yoko", user.name.c_str());
	EXPECT_STREQ("Yoko", user.nickname.c_str());
	EXPECT_STREQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl.c_str());
}

TEST(CacooApi, account)
{
	MockServer* mock = new MockServer();
	CacooApi api;
	api.setServer(mock);
	CacooUser user = api.Account();

	EXPECT_STREQ("yoko", user.name.c_str());
	EXPECT_STREQ("Yoko", user.nickname.c_str());
	EXPECT_STREQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl.c_str());
}
