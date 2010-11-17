#pragma once
#include "stdafx.h"

#include "CacooChatMessage.hpp"
#include "CacooDiagram.hpp"
#include "CacooFolder.hpp"
#include "CacooHandler.h"
#include "CacooSheet.hpp"
#include "CacooUser.hpp"

class CacooApi
{
private:
	boost::shared_ptr<CacooHandler> handler;

public:
	CacooApi(boost::shared_ptr<CacooHandler>);
	~CacooApi(void);
	std::vector<CacooDiagram> Diagrams();
	CacooDiagram Diagram(const std::string& diagramId);
	CacooUser Users(const std::string& name);
	void Image(const std::string& name);
	std::vector<CacooChatMessage> ChatMessages(const std::string& diagramId);
	std::vector<CacooFolder> Folders();
	CacooUser Account(void);
	static void parseXml(std::map<std::string, std::string>&, const std::string& xmlData);
	static boost::shared_ptr<TiXmlDocument> parseXml(const std::string& xmlData);
	static void parseSubItem(std::map<std::string, std::string>&, TiXmlElement*);
};
