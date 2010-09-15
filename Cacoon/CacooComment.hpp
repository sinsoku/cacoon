#pragma once
#include "stdafx.h"

#include "CacooUser.hpp"

class CacooComment
{
private:
	std::map<std::string, boost::any> data;

public:
	CacooComment() {}

	CacooComment(TiXmlElement* root) {
		TiXmlElement* e = root->FirstChildElement();
		data[e->Value()] = CacooUser(e);
		e = e->NextSiblingElement();

		while( e != NULL ) {
			std::string key( e->Value() );
			std::string value( e->GetText() );
			data[key] = value;

			e = e->NextSiblingElement();
		}
	}

	~CacooComment() {}

	CacooUser getUser() {
		return boost::any_cast<CacooUser>(data["user"]);
	}

	std::string getContent() {
		return boost::any_cast<std::string>(data["content"]);
	}

	time_t getCreated() {
		std::string created = boost::any_cast<std::string>(data["created"]);
		return 0; // fake it
	}

	time_t getUpdated() {
		std::string updated = boost::any_cast<std::string>(data["updated"]);
		return 0; // fake it
	}
};
