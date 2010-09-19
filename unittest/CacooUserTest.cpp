#include "stdafx.h"

#include "CacooApi.h"
#include "CacooUser.hpp"

TEST(CacooUser, init)
{
	char rawXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<user>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</user>";
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(rawXmlData);
	CacooUser actual( doc->RootElement() );

	EXPECT_EQ("yoko", actual.getName() );
	EXPECT_EQ("Yoko", actual.getNickName() );
	EXPECT_EQ("https://cacoo.com/account/yoko/image/32x32", actual.getImageUrl() );
}
