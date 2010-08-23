#pragma once
#include "CacooServer.h"

class CacooUser
{
public:
	std::string name;
	std::string nickname;
	std::string imageUrl;
};

class CacooApi
{
private:
	CacooServer* cacooServer;

public:
	CacooApi(void);
	~CacooApi(void);
	CacooUser users(const std::string& name);
	CacooUser account(void);
	static CacooUser parseUser(const std::string& xmlData);
	void setServer(CacooServer* server);
};
