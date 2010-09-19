#pragma once
#include "stdafx.h"

#include "CacooUser.hpp"

class CacooChatMessage
{
public:
	CacooUser user;
	std::string content;
	time_t created;
};
