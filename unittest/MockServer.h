#pragma once
#include "CacooServer.h"
class MockServer :
	public CacooServer
{
public:
	MockServer(void);
	virtual ~MockServer(void);
	virtual std::string get(const std::string&);
	static std::string MockServer::createDiagrams(void);
	static std::string MockServer::createDiagram(void);
	static std::string MockServer::createChatMesseages(void);
	static std::string MockServer::createFolders(void);
	static std::string MockServer::createUsers(void);
	static std::string MockServer::createAccount(void);
};