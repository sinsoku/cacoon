#pragma once
#include "stdafx.h"

class CacooHandler
{
public:
	CacooHandler(void);
	virtual ~CacooHandler(void);
	virtual std::string get(const std::string& url);
};

