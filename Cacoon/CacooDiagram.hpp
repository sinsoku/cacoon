#pragma once
#include "stdafx.h"

#include "CacooComment.hpp"
#include "CacooSheet.hpp"
#include "CacooUser.hpp"

class CacooDiagram
{
private:
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
	~CacooDiagram() {}
};
