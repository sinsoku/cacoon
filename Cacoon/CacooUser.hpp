#pragma once
#include "stdafx.h"

class CacooUser
{
private:
	std::string name;
	std::string nickname;
	std::string imageUrl;
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
	std::string getName() { return name; }
	std::string getNickName() { return nickname; }
	std::string getImageUrl() { return imageUrl; }
};
