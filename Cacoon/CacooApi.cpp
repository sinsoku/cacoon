#include "StdAfx.h"
#include "CacooApi.h"
#include <string>
#include <vector>
CacooApi::CacooApi(void)
{
}


CacooApi::~CacooApi(void)
{
}

std::vector<CacooDiagram> CacooApi::Diagrams()
{
	std::string url = "http://cacoo.com/api/v1/diagrams.xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseDiagrams(resXmlData);
}

//CacooDiagram CacooApi::Diagram(const std::string& diagramId)
//{
//	std::string url = "http://cacoo.com/api/v1/diagrams" + diagramId + ".xml";
//	std::string resXmlData = cacooServer->get(url);
//	return CacooApi::parseDiagram(resXmlData);
//}
//
//void CacooApi::Image(const std::string& diagramId)
//{
//	throw std::exception();
//}
//
//std::vector<CacooChatMessage> CacooApi::ChatMessages(const std::string& diagramId)
//{
//	std::string url = "http://cacoo.com/api/v1/diagrams" + diagramId + "/chat/messages.xml";
//	std::string resXmlData = cacooServer->get(url);
//	return CacooApi::parseChatMessages(resXmlData);
//}
//
//std::vector<CacooFolder> CacooApi::Folders()
//{
//	std::string url = "http://cacoo.com/api/v1/folders.xml";
//	std::string resXmlData = cacooServer->get(url);
//	return CacooApi::parseFolders(resXmlData);
//}

CacooUser CacooApi::users(const std::string& name)
{
	std::string url = "http://cacoo.com/api/v1/users/" + name + ".xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseUser(resXmlData);
}

CacooUser CacooApi::account()
{
	std::string url = "http://cacoo.com/api/v1/account.xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseUser(resXmlData);
}

void CacooApi::setServer(CacooServer* server)
{
	cacooServer = server;
}

std::vector<CacooDiagram> parseDiagrams(const std::string& xmlData)
{
	throw std::exception();
	std::vector<CacooDiagram> cdv;
	return cdv;
}
//
//CacooDiagram parseDiagram(const std::string& xmlData)
//{
//	throw std::exception();
//	CacooDiagram cd;
//	return cd;
//}
//
//std::vector<CacooChatMessage> parseChatMessages(const std::string& xmlData)
//{
//	throw std::exception();
//	std::vector<CacooChatMessage> ccmv;
//	return ccmv;
//}
//
//std::vector<CacooFolder> parseFolders(const std::string& xmlData)
//{
//	throw std::exception();
//	std::vector<CacooFolder> cfv;
//	return cfv;
//}

CacooUser CacooApi::parseUser(const std::string& xmlData)
{
	// テンプファイルに書込み
	char xmltmpfile[] = "xmltmp.xml";
	std::ofstream ofs(xmltmpfile);
	ofs << xmlData;
	ofs.close();

	// TinyXmlで読込み
	TiXmlDocument doc(xmltmpfile);
	doc.LoadFile();

	// テンプファイルの削除
	remove(xmltmpfile);

	CacooUser cu;
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* e = root->FirstChildElement();
	cu.name = e->GetText();

	TiXmlElement* e1 = e->NextSiblingElement();
	cu.nickname = e1->GetText();

	TiXmlElement* e2 = e1->NextSiblingElement();
	cu.imageUrl = e2->GetText();

	return cu;
}
