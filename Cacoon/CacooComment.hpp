#pragma once
#include "stdafx.h"

#include "CacooUser.hpp"
#include <boost/assign.hpp>
typedef boost::char_separator<char> char_separator;
typedef boost::tokenizer<char_separator> tokenizer;

class CacooComment
{
private:
	std::map<std::string, boost::any> data;

public:
	CacooComment() {}

	CacooComment(TiXmlElement* root) {
		TiXmlElement* e = root->FirstChildElement();
		while( e != NULL ) {
			if ( !strcmp( e->Value(), "user") ) {
				data[e->Value()] = CacooUser(e);
			} else if ( !strcmp( e->Value(), "created") || !strcmp( e->Value(), "updated") ) {
				data[e->Value()] = timeFromString( e->GetText() );
			} else {
				std::string key( e->Value() );
				std::string value( e->GetText() );
				data[key] = value;
			}

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
		return boost::any_cast<time_t>(data["created"]);
	}

	time_t getUpdated() {
		return boost::any_cast<time_t>(data["created"]);
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
