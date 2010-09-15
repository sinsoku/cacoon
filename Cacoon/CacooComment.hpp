#pragma once
#include "stdafx.h"

#include "CacooUser.hpp"

class CacooComment
{
public:
	CacooUser user;
	std::string content;
	time_t created;
	time_t updated;
};
