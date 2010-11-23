#include "stdafx.h"
#include "HttpClient.h"
#include "HttpConnection.h"
#include "HttpsConnection.h"

HttpClient HttpClient::httpClient;	// �B��̃C���X�^���X (�����Ŏ����I�ɃR���X�g���N�^���Ă΂��)

// �v���O�����̏��������ɌĂ΂��
HttpClient::HttpClient()
{
	this->data = new WSAData();
	WSAStartup( MAKEWORD( 2, 0 ), this->data );
}

// �v���O�����̏I�����ɌĂ΂��
HttpClient::~HttpClient()
{
	WSACleanup();
	delete this->data;
}

// HTTP �ڑ��N���X�̍쐬
Connection HttpClient::CreateHttpConnection( const std::string & host )
{
	return Connection( new HttpConnection( host ) );
}

// HTTPS �ڑ��N���X�̍쐬
Connection HttpClient::CreateHttpsConnection( const std::string & host )
{
	return Connection( new HttpsConnection( host ) );
}

// URL �ɊȒP�ɃA�N�Z�X���邽�߂̐ÓI���\�b�h
Response HttpClient::Connect( const std::string & method, const std::string & url, const HeaderMap & header )
{
	int prefixLength = url.find( "://" ) + 3;	// "https://" �̒���
	int rootLength = url.substr( prefixLength ).find( "/" );
	std::string root = url.substr( prefixLength, rootLength );	// "https://(xxxx)/**" �� (xxxx) �𒊏o
	std::string endpoint = url.substr( prefixLength + rootLength );	// ��� (xxxx) �ȍ~�𒊏o

	Connection conn = ( url.substr( 0, 5 ) == "https" )
		? HttpClient::CreateHttpsConnection( root )
		: HttpClient::CreateHttpConnection( root );

	return conn.Request( "GET", endpoint, header );
}
