#include "stdafx.h"

#include "CacooApi.h"
#include "CacooDiagram.hpp"

TEST(CacooDiagram, init)
{
	char rawXmlData[] =
		"<diagram>"
		"  <url>https://cacoo.com/diagrams/00e77f4dc9973517</url>"
		"  <imageUrl>https://cacoo.com/diagrams/00e77f4dc9973517.png</imageUrl>"
		"  <imageUrlForApi>https://cacoo.com/api/v1/diagrams/00e77f4dc9973517.png</imageUrlForApi>"
		"  <diagramId>00e77f4dc9973517</diagramId>"
		"  <title>shape1</title>"
		"  <security>url</security>"
		"  <ownerName>yoko</ownerName>"
		"  <ownerNickname>Yoko</ownerNickname>"
		"  <owner>"
		"    <name>yoko</name>"
		"    <nickname>Yoko</nickname>"
		"    <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"  </owner>"
		"  <editing>false</editing>"
		"  <own>true</own>"
		"  <shared>true</shared>"
		"  <sheetCount>0</sheetCount>"
		"  <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"  <updated>Mon, 10 Aug 2009 17:00:00 +0900</updated>"
		"</diagram>";
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(rawXmlData);
	CacooDiagram actual( doc->RootElement() );

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
