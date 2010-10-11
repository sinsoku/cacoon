#include "StdAfx.h"
#include "CacooApi.h"

CacooApi::CacooApi(boost::shared_ptr<CacooServer> server)
{
	cacooServer = server;
}


CacooApi::~CacooApi(void)
{
}

std::vector<CacooDiagram> CacooApi::Diagrams()
{
	std::string url = "https://cacoo.com/api/v1/diagrams.xml";
	std::string resXmlData = cacooServer->get(url);
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);

	//return CacooDiagrams( doc->RootElement() );
	throw std::exception();
}

CacooDiagram CacooApi::Diagram(const std::string& diagramId)
{
	std::string url = "https://cacoo.com/api/v1/diagrams/" + diagramId + ".xml";
	std::string resXmlData = cacooServer->get(url);
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);

	return CacooDiagram( doc->RootElement() );
}

void CacooApi::Image(const std::string& diagramId)
{
	throw std::exception();
}

std::vector<CacooChatMessage> CacooApi::ChatMessages(const std::string& diagramId)
{
	std::string url = "https://cacoo.com/api/v1/diagrams/" + diagramId + "/chat/messages.xml";
	std::string resXmlData = cacooServer->get(url);
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);

	//return CacooChatMessage( doc->RootElement() );
	throw std::exception();
}

std::vector<CacooFolder> CacooApi::Folders()
{
	std::string url = "https://cacoo.com/api/v1/folders.xml";
	std::string resXmlData = cacooServer->get(url);
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);

	//return CacooFolder( doc->RootElement() );
	throw std::exception();
}

CacooUser CacooApi::Users(const std::string& name)
{
	std::string url = "https://cacoo.com/api/v1/users/" + name + ".xml";
	std::string resXmlData = cacooServer->get(url);
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);

	return CacooUser( doc->RootElement() );
}

CacooUser CacooApi::Account()
{
	std::string url = "https://cacoo.com/api/v1/account.xml";
	std::string resXmlData = cacooServer->get(url);
	boost::shared_ptr<TiXmlDocument> doc = CacooApi::parseXml(resXmlData);

	return CacooUser( doc->RootElement() );
}

boost::shared_ptr<TiXmlDocument> CacooApi::parseXml(const std::string& rawXmlData)
{
	// �e���v�t�@�C���ɏ�����
	char xmltmpfile[] = "xmltmp.xml";
	std::ofstream ofs(xmltmpfile);
	ofs << rawXmlData;
	ofs.close();

	// TinyXml�œǍ���
	boost::shared_ptr<TiXmlDocument> doc;
	doc = boost::shared_ptr<TiXmlDocument>( new TiXmlDocument(xmltmpfile) );
	doc->LoadFile();

	// �e���v�t�@�C���̍폜
	remove(xmltmpfile);

	// TinyXmlDocument�̃|�C���^��Ԃ�
	return doc;
}
