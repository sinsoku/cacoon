#pragma once
#include "stdafx.h"

class CacooUser
{
public:
	std::string name;
	std::string nickname;
	std::string imageUrl;
	void valueOf(std::map<std::string, std::string> xmlData) {
		name     = xmlData["name"];
		nickname = xmlData["nickname"];
		imageUrl = xmlData["imageUrl"];
	}
public:
	CacooUser() {}
	CacooUser(TiXmlDocument& doc) {
		TiXmlElement* root = doc.RootElement();

		TiXmlElement* e = root->FirstChildElement();
		name = e->GetText();

		TiXmlElement* e1 = e->NextSiblingElement();
		nickname = e1->GetText();

		TiXmlElement* e2 = e1->NextSiblingElement();
		imageUrl = e2->GetText();
	}
	~CacooUser() {}
};
