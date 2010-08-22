#include "stdafx.h"
#include "CacooApi.h"

TEST(CacooApi, users) 
{
	CacooApi api;
	CacooUser user = api.users("yoko");

	EXPECT_STREQ("yoko", user.name.c_str());
	EXPECT_STREQ("Yoko", user.nickname.c_str());
	EXPECT_STREQ("https://cacoo.com/account/yoko/image/32x32", user.imageUrl.c_str());
}