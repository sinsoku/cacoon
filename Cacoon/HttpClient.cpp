#include "stdafx.h"
#include "HttpClient.h"
#include "HttpConnection.h"
#include "HttpsConnection.h"
#include "MockConnection.h"

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