#include "StdAfx.h"
#include "CacooApi.h"

CacooApi::CacooApi(void)
{
}


CacooApi::~CacooApi(void)
{
}

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