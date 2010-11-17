#pragma once
#include "CacooHandler.h"
class MockHandler :
	public CacooHandler
{
public:
	MockHandler(void);
	virtual ~MockHandler(void);
	virtual std::string get(const std::string&);
	static std::string MockHandler::createDiagrams(void);
	static std::string MockHandler::createDiagram(void);
	static std::string MockHandler::createChatMesseages(void);
	static std::string MockHandler::createFolders(void);
	static std::string MockHandler::createUsers(void);
	static std::string MockHandler::createAccount(void);
};