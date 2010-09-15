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
};
