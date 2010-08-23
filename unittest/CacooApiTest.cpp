#include "stdafx.h"
#include "CacooApi.h"
#include "MockServer.h"

TEST(CacooApi, paserUser)
{
}

TEST(CacooApi, users) 
{
	MockServer* mock = new MockServer();
	CacooApi api;
	api.setServer(mock);
	CacooUser user = api.users("yoko");

	EXPECT_STREQ("yoko", user.name.c_str());
	EXPECT_STREQ("Yoko", user.nickname.c_str());
	EXPECT_STREQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl.c_str());
	delete mock;
}

TEST(CacooApi, account)
{
	MockServer* mock = new MockServer();
	CacooApi api;
	api.setServer(mock);
	CacooUser user = api.account();

	EXPECT_STREQ("yoko", user.name.c_str());
	EXPECT_STREQ("Yoko", user.nickname.c_str());
	EXPECT_STREQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl.c_str());
	delete mock;
}
