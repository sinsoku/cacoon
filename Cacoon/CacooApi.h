#pragma once
#include "CacooServer.h"

class CacooUser
{
public:
	std::string name;
	std::string nickname;
	std::string imageUrl;
};

class CacooSheet
{
public:
	std::string url;
	std::string imageUrl;
	std::string imageUrlForApi;
	std::string uid;
	std::string name;
	std::string width;
	std::string height;
};

class CacooComment
{
public:
	CacooUser user;
	std::string content;
	time_t created;
	time_t updated;
};

class CacooDiagram
{
public:
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
	bool editing; // ñ≥Ç¢ÅH
	bool own;
	bool shared;
	std::string folderName;
	int sheetCount;
	time_t created;
	time_t updated;
	std::vector<CacooSheet> sheets;
	std::vector<CacooComment> comments;
};

class CacooChatMessage
{
public:
	CacooUser user;
	std::string content;
	time_t created;
};

class CacooFolder
{
public:
	int folderId;
	std::string folderName;
	std::string type;
	time_t created;
	time_t updated;
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
