#include "StdAfx.h"
#include "CacooApi.h"

CacooApi::CacooApi(void)
{
}


CacooApi::~CacooApi(void)
{
}

CacooUser CacooApi::users(const std::string &name)
{
	char resXmlData[] =
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
		"<user>"
		"<name>yoko</name>"
		"<nickname>Yoko</nickname>"
		"<imageUrl>https://cacoo.com/account/yoko/image/32x32</imageUrl>"
		"</user>";
	CacooUser cu;

	// �e���v�t�@�C���ɏ�����
	char xmltmpfile[] = "xmltmp.xml";
	std::ofstream ofs(xmltmpfile);
	ofs << resXmlData;
	ofs.close();

	// TinyXml�œǍ���
	TiXmlDocument doc(xmltmpfile);
	doc.LoadFile();

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* e = root->FirstChildElement();
	cu.name = e->GetText();

	TiXmlElement* e1 = e->NextSiblingElement();
	cu.nickname = e1->GetText();

	TiXmlElement* e2 = e1->NextSiblingElement();
	cu.imageUrl = e2->GetText();

	// �e���v�t�@�C���̍폜
	remove(xmltmpfile);

	return cu;
}

CacooUser CacooApi::account()
{
	return users("yoko");
}

void CacooApi::setServer(const CacooServer &server)
{
	cacooServer = server;
}