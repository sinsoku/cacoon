#pragma once
#include "stdafx.h"

#include "CacooChatMessage.hpp"
#include "CacooDiagram.hpp"
#include "CacooFolder.hpp"
#include "CacooServer.h"
#include "CacooSheet.hpp"
#include "CacooUser.hpp"

class CacooApi
{
private:
	boost::shared_ptr<CacooServer> cacooServer;

public:
	CacooApi(boost::shared_ptr<CacooServer>);
	~CacooApi(void);
	std::vector<CacooDiagram> Diagrams();
	CacooDiagram Diagram(const std::string& diagramId);
	CacooUser Users(const std::string& name);
	void Image(const std::string& name);
	std::vector<CacooChatMessage> ChatMessages(const std::string& diagramId);
	std::vector<CacooFolder> Folders();
	CacooUser Account(void);
	static std::vector<CacooDiagram> parseDiagrams(const std::string& xmlData);
	static CacooDiagram parseDiagram(const std::string& xmlData);
	static std::vector<CacooChatMessage> parseChatMessages(const std::string& xmlData);
	static std::vector<CacooFolder> parseFolders(const std::string& xmlData);
	static CacooUser parseUser(const std::string& xmlData);
	static void parseXml(std::map<std::string, std::string>&, const std::string& xmlData);
	static boost::shared_ptr<TiXmlDocument> parseXml(const std::string& xmlData);
	static void parseSubItem(std::map<std::string, std::string>&, TiXmlElement*);
};
