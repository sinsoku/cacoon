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
			} else if ( !strcmp( e->Value(), "created") || !strcmp( e->Value(), "updated") ) {
				data[e->Value()] = timeFromString( e->GetText() );
			} else if ( !strcmp( e->Value(), "sheets") ) {
				// –¢ŽÀ‘•‚Ì‚½‚ßA”ò‚Î‚·
			} else if ( !strcmp( e->Value(), "comments") ) {
				// –¢ŽÀ‘•‚Ì‚½‚ßA”ò‚Î‚·
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
		return boost::any_cast<time_t>(data["created"]);
	}

	time_t getUpdated() {
		return boost::any_cast<time_t>(data["updated"]);
	}

	static time_t timeFromString(const std::string& strdate) {
		const std::map<std::string, int> MONTH_MAP = boost::assign::map_list_of
			("Jan", 1)("Feb", 2)("Mar", 3)("Apr", 4)("May", 5)("Jun", 6)
			("Jul", 7)("Aug", 8)("Sep", 9)("Oct", 10)("Nov", 11)("Dec", 12);
		std::vector<std::string> date;
		parseDate(date, strdate);

		struct tm tm_date;
		tm_date.tm_year = boost::lexical_cast<int>( date[3] ) - 1900;
		tm_date.tm_mon  = MONTH_MAP.find(date[2])->second - 1;
		tm_date.tm_mday = boost::lexical_cast<int>( date[1] );
		tm_date.tm_hour = boost::lexical_cast<int>( date[4] );
		tm_date.tm_min  = boost::lexical_cast<int>( date[5] );
		tm_date.tm_sec  = boost::lexical_cast<int>( date[6] );

		return mktime(&tm_date);
	}

	static void parseDate(std::vector<std::string>& sv, const std::string& strdate) {
		char_separator sep(" ,:", "", boost::drop_empty_tokens);
		tokenizer tokens(strdate, sep);

		BOOST_FOREACH(std::string v, tokens) {
			sv.push_back( v );
		}
	}
};
