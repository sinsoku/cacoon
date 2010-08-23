#include "StdAfx.h"
#include "MockServer.h"


MockServer::MockServer(void)
{
}


MockServer::~MockServer(void)
{
}

std::string MockServer::get(const std::string& url)
{
	return MockServer::createUsers();
}

std::string MockServer::createDiagrams()
{
	return "";
}

std::string MockServer::createDiagram()
{
	return "";
}

std::string MockServer::createChatMesseages()
{
	return "";
}

std::string MockServer::createFolders()
{
	return "";
}

std::string MockServer::createUsers()
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<user>"
		"<name>yoko</name>"
		"<nickname>Yoko</nickname>"
		"<imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</user>";

	return resXmlData;
}

std::string MockServer::createAccount()
{
	return "";
}