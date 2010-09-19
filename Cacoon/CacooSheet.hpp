#pragma once
#include "stdafx.h"

class CacooSheet
{
private:
	std::map<std::string, boost::any> data;

public:
	CacooSheet() {}

	CacooSheet(TiXmlElement* root) {
		TiXmlElement* e = root->FirstChildElement();
		while( e != NULL ) {
			std::string key( e->Value() );
			std::string value( e->GetText() );
			data[key] = value;

			e = e->NextSiblingElement();
		}
	}

	~CacooSheet() {}

	std::string getUrl() {
		return boost::any_cast<std::string>(data["url"]);
	}

	std::string getImageUrl() {
		return boost::any_cast<std::string>(data["imageUrl"]);
	}

	std::string getImageUrlForApi() {
		return boost::any_cast<std::string>(data["imageUrlForApi"]);
	}

	std::string getUid() {
		return boost::any_cast<std::string>(data["uid"]);
	}

	std::string getName() {
		return boost::any_cast<std::string>(data["name"]);
	}

	std::string getWidth() {
		return boost::any_cast<std::string>(data["width"]);
	}

	std::string getHeight() {
		return boost::any_cast<std::string>(data["height"]);
	}

};
