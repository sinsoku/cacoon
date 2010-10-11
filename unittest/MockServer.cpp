#include "StdAfx.h"
#include "MockServer.h"


MockServer::MockServer(void)
{
}


MockServer::~MockServer(void)
{
}

std::string MockServer::get(const std::string& uri)
{
	std::string base = "https://cacoo.com/api/v1/";

	if (base + "users/yoko.xml" == uri) {
		return MockServer::createUsers();
	} else if (base + "account.xml" == uri) {
		return MockServer::createAccount();
	} else if (base + "diagrams/00e77f4dc9973517.xml" == uri) {
		return MockServer::createDiagram();
	}
	return "";
}

std::string MockServer::createDiagrams()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		""
		"<diagrams>"
		"  <result>"
		"    <diagram>"
		"      <url>https://cacoo.com/diagrams/00e77f4dc9973517</url>"
		"      <imageUrl>https://cacoo.com/diagrams/00e77f4dc9973517.png</imageUrl>"
		""
		"      <imageUrlForApi>https://cacoo.com/api/v1/diagrams/00e77f4dc9973517.png</imageUrlForApi>"
		"      <diagramId>00e77f4dc9973517</diagramId>"
		"      <title>shape1</title>"
		"      <security>url</security>"
		""
		"      <ownerName>yoko</ownerName>"
		"      <ownerNickname>Yoko</ownerNickname>"
		"      <owner>"
		"        <name>yoko</name>"
		"        <nickname>Yoko</nickname>"
		"        <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"      </owner>"
		"      <editing>false</editing>"
		"      <own>true</own>"
		""
		"      <shared>true</shared>"
		"      <sheetCount>0</sheetCount>"
		"      <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"      <updated>Mon, 10 Aug 2009 17:00:00 +0900</updated>"
		""
		"    </diagram>"
		"  </result>"
		"  <count>2</count>"
		""
		"</diagrams>";

	return resXmlData;
}

std::string MockServer::createDiagram()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<diagram>"
		"  <url>https://cacoo.com/diagrams/00e77f4dc9973517</url>"
		""
		"  <imageUrl>https://cacoo.com/diagrams/00e77f4dc9973517.png</imageUrl>"
		"  <imageUrlForApi>https://cacoo.com/api/v1/diagrams/00e77f4dc9973517.png</imageUrlForApi>"
		"  <diagramId>00e77f4dc9973517</diagramId>"
		"  <title>shape1</title>"
		""
		"  <security>url</security>"
		"  <ownerName>yoko</ownerName>"
		"  <ownerNickname>Yoko</ownerNickname>"
		"  <owner>"
		"    <name>yoko</name>"
		"    <nickname>Yoko</nickname>"
		"    <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"  </owner>"
		""
		"  <own>true</own>"
		""
		"  <shared>false</shared>"
		"  <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"  <updated>Mon, 10 Aug 2009 17:00:00 +0900</updated>"
		""
		"  <sheets>"
		"    <sheet>"
		"      <url>https://cacoo.com/diagrams/00e77f4dc9973517#aaaa</url>"
		"      <imageUrl>https://cacoo.com/diagrams/00e77f4dc9973517-aaaa.png</imageUrl>"
		"      <imageUrlForApi>https://cacoo.com/api/v1/diagrams/00e77f4dc9973517-aaaa.png</imageUrlForApi>"
		""
		"      <uid>aaaa</uid>"
		"      <name>sheet1</name>"
		"      <width>200</width>"
		"      <height>100</height>"
		""
		"    </sheet>"
		"  </sheets>"
		""
		"  <comments>"
		"    <comment>"
		"      <user>"
		"        <name>yoko</name>"
		"        <nickname>Yoko</nickname>"
		"        <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"      </user>"
		"      <content>comment 1</content>"
		"      <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"      <updated>Mon, 10 Aug 2009 17:00:00 +0900</updated>"
		"    </comment>"
		"  </comments>"
		"</diagram>";

	return resXmlData;
}

std::string MockServer::createChatMesseages()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<messages>"
		"  <result>"
		"    <message>"
		"      <user>"
		"        <name>yoko</name>"
		"        <nickname>Yoko</nickname>"
		"        <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"      </user>"
		"      <content>message 1</content>"
		"      <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"    </message>"
		"  </result>"
		"</messages>";

	return resXmlData;
}

std::string MockServer::createFolders()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<folders>"
		"  <result>"
		"    <folder>"
		"      <folderId>10001lt;/folderId>"
		"      <folderName>Folder 1</folderName>"
		"      <type>normal</type>"
		"      <created>Mon, 10 Aug 2009 17:00:00 +0900</created>"
		"      <updated>Mon, 10 Aug 2009 17:00:00 +0900</updated>"
		"    </folder>"
		"  </result>"
		"</folders>";

	return resXmlData;
}

std::string MockServer::createUsers()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<user>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</user>";

	return resXmlData;
}

std::string MockServer::createAccount()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<account>"
		"  <name>yoko</name>"
		"  <nickname>Yoko</nickname>"
		"  <imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</account>";

	return resXmlData;
}