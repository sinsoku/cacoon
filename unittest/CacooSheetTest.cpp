#include "stdafx.h"

#include "CacooApi.h"
#include "CacooSheet.hpp"

TEST(CacooSheet, init)
{
	char rawXmlData[] =
		"<sheet>"
		"  <url>https://cacoo.com/diagrams/00e77f4dc9973517#aaaa</url>"
		"  <imageUrl>https://cacoo.com/diagrams/00e77f4dc9973517-aaaa.png</imageUrl>"
		"  <imageUrlForApi>https://cacoo.com/api/v1/diagrams/00e77f4dc9973517-aaaa.png</imageUrlForApi>"
		"  <uid>aaaa</uid>"
		"  <name>sheet1</name>"
		"  <width>200</width>"
		"  <height>100</height>"
		"</sheet>";
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(rawXmlData);
	CacooSheet actual( doc->RootElement() );

	EXPECT_EQ("https://cacoo.com/diagrams/00e77f4dc9973517#aaaa", actual.getUrl() );
	EXPECT_EQ("https://cacoo.com/diagrams/00e77f4dc9973517-aaaa.png", actual.getImageUrl() );
	EXPECT_EQ("https://cacoo.com/api/v1/diagrams/00e77f4dc9973517-aaaa.png", actual.getImageUrlForApi() );
	EXPECT_EQ("aaaa", actual.getUid() );
	EXPECT_EQ("sheet1", actual.getName() );
	EXPECT_EQ("200", actual.getWidth() );
	EXPECT_EQ("100", actual.getHeight() );
}
