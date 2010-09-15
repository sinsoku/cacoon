#pragma once
#include "stdafx.h"
#include <iostream>

class CacooUser
{
private:
	std::map<std::string, boost::any> data;

public:
	CacooUser() {}

	CacooUser(TiXmlElement* root) {
		TiXmlElement* e = root->FirstChildElement();
		while( e != NULL ) {
			std::string key( e->Value() );
			std::string value( e->GetText() );
			data[key] = value;

			e = e->NextSiblingElement();
		}
	}

	~CacooUser() {}

	std::string getName() {
		return boost::any_cast<std::string>(data["name"]);
	}

	std::string getNickName() {
		return boost::any_cast<std::string>(data["nickname"]);
	}

	std::string getImageUrl() {
		return boost::any_cast<std::string>(data["imageUrl"]);
	}
};
