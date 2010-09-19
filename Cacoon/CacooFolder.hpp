#pragma once
#include "stdafx.h"

class CacooFolder
{
public:
	int folderId;
	std::string folderName;
	std::string type;
	time_t created;
	time_t updated;
};
