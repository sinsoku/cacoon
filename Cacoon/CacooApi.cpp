#include "StdAfx.h"
#include "CacooApi.h"
#include <string>
#include <vector>

CacooApi::CacooApi(void)
{
	cacooServer = boost::shared_ptr<CacooServer>(new CacooServer());
}


CacooApi::~CacooApi(void)
{
}

std::vector<CacooDiagram> CacooApi::Diagrams()
{
	std::string url = "http://cacoo.com/api/v1/diagrams.xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseDiagrams(resXmlData);
}

CacooDiagram CacooApi::Diagram(const std::string& diagramId)
{
	std::string url = "http://cacoo.com/api/v1/diagrams" + diagramId + ".xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseDiagram(resXmlData);
}

void CacooApi::Image(const std::string& diagramId)
{
	throw std::exception();
}

std::vector<CacooChatMessage> CacooApi::ChatMessages(const std::string& diagramId)
{
	std::string url = "http://cacoo.com/api/v1/diagrams" + diagramId + "/chat/messages.xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseChatMessages(resXmlData);
}

std::vector<CacooFolder> CacooApi::Folders()
{
	std::string url = "http://cacoo.com/api/v1/folders.xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseFolders(resXmlData);
}

CacooUser CacooApi::Users(const std::string& name)
{
	std::string url = "http://cacoo.com/api/v1/users/" + name + ".xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseUser(resXmlData);
}

CacooUser CacooApi::Account()
{
	std::string url = "http://cacoo.com/api/v1/account.xml";
	std::string resXmlData = cacooServer->get(url);
	return CacooApi::parseUser(resXmlData);
}

void CacooApi::setServer(boost::shared_ptr<CacooServer> server)
{
	cacooServer = server;
}

std::vector<CacooDiagram> CacooApi::parseDiagrams(const std::string& xmlData)
{
	throw std::exception();
	std::vector<CacooDiagram> cdv;
	return cdv;
}

CacooDiagram CacooApi::parseDiagram(const std::string& xmlData)
{
	throw std::exception();
	CacooDiagram cd;
	return cd;
}

std::vector<CacooChatMessage> CacooApi::parseChatMessages(const std::string& xmlData)
{
	throw std::exception();
	std::vector<CacooChatMessage> ccmv;
	return ccmv;
}

std::vector<CacooFolder> CacooApi::parseFolders(const std::string& xmlData)
{
	throw std::exception();
	std::vector<CacooFolder> cfv;
	return cfv;
}

CacooUser CacooApi::parseUser(const std::string& rawXmlData)
{
	std::map<std::string, std::string> xmlData;
	CacooApi::parseXml(xmlData, rawXmlData);

	// map<string, string>からデータを設定
	CacooUser cu;
	cu.valueOf(xmlData);

	return cu;
}

void CacooApi::parseXml(std::map<std::string, std::string>& xmlData, const std::string& rawXmlData)
{
	// テンプファイルに書込み
	char xmltmpfile[] = "xmltmp.xml";
	std::ofstream ofs(xmltmpfile);
	ofs << rawXmlData;
	ofs.close();

	// TinyXmlで読込み
	TiXmlDocument doc(xmltmpfile);
	doc.LoadFile();

	// テンプファイルの削除
	remove(xmltmpfile);

	// XMLのrootを取得し、ツリー構造を読込み。
	TiXmlElement* root = doc.RootElement();
	parseSubItem(xmlData, root);
}

void CacooApi::parseSubItem(std::map<std::string, std::string>& xmlData, TiXmlElement* e)
{
	if(e == NULL) {
		return;
	}
	for(e ; e ; e = e->NextSiblingElement())
	{
		const char* key   = e->Value();
		const char* value = e->GetText();
		if(value != NULL) {
			xmlData.insert( std::make_pair(key, value) );
		}
		parseSubItem(xmlData, e->FirstChildElement());
	}
}