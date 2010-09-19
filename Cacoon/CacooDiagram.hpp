#pragma once
#include "stdafx.h"

#include "CacooComment.hpp"
#include "CacooSheet.hpp"
#include "CacooUser.hpp"

class CacooDiagram
{
private:
	std::map<std::string, boost::any> data;

	std::string url;
	std::string imageUrl;
	std::string imageUrlForApi;
	std::string diagramId;
	std::string title;
	std::string description;
	std::string security;
	std::string ownerName;
	std::string ownerNickName;
	CacooUser owner;
	bool editing;
	bool own;
	bool shared;
	std::string folderName;
	int sheetCount;
	time_t created;
	time_t updated;
	std::vector<CacooSheet> sheets;
	std::vector<CacooComment> comments;
public:
	CacooDiagram() {}

	CacooDiagram(TiXmlElement* root) {
		TiXmlElement* e = root->FirstChildElement();
		while( e != NULL ) {
			if ( !strcmp( e->Value(), "owner") ) {
				data[e->Value()] = CacooUser(e);
			} else if ( !strcmp( e->Value(), "sheets") ) {
				// �������̂��߁A��΂�
			} else if ( !strcmp( e->Value(), "comments") ) {
				// �������̂��߁A��΂�
			} else {
				std::string key( e->Value() );
				std::string value( e->GetText() );
				data[key] = value;
			}

			e = e->NextSiblingElement();
		}
	}

	~CacooDiagram() {}

	time_t getCreated() {
		std::string created = boost::any_cast<std::string>(data["created"]);
		return 0; // fake it
	}

	time_t getUpdated() {
		std::string updated = boost::any_cast<std::string>(data["updated"]);
		return 0; // fake it
	}
};
