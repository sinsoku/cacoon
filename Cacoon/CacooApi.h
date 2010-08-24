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
	bool editing;
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
	std::vector<CacooDiagram> Diagrams();
	//CacooDiagram Diagram(const std::string& diagramId);
	CacooUser users(const std::string& name);
	//void Image(const std::string& name);
	//std::vector<CacooChatMessage> CacooApi::ChatMessages(const std::string& diagramId);
	//std::vector<CacooFolder> CacooApi::Folders();
	CacooUser account(void);
	static std::vector<CacooDiagram> parseDiagrams(const std::string& xmlData);
	//static CacooDiagram parseDiagram(const std::string& xmlData);
	//static std::vector<CacooChatMessage> parseChatMessages(const std::string& xmlData);
	//static std::vector<CacooFolder> parseFolders(const std::string& xmlData);
	static CacooUser parseUser(const std::string& xmlData);
	void setServer(CacooServer* server);
};
