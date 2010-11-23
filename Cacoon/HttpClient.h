#pragma once
#include "stdafx.h"
#include "Connection.h"

struct WSAData;
// HTTP �� HTTPS �ɂ��ڑ����쐬���邽�߂̃t�@�N�g���[�N���X
class HttpClient
{
public:
	static Connection CreateHttpConnection( const std::string & host );
	static Connection CreateHttpsConnection( const std::string & host );

	// URL �ɊȒP�ɃA�N�Z�X���邽�߂̐ÓI���\�b�h
	static Response Connect( const std::string & method, const std::string & url, const HeaderMap & header = HeaderMap() );
	
	~HttpClient();

private:

	HttpClient();	// �쐬�֎~
	WSAData * data;
	static HttpClient httpClient;	// �B��̃C���X�^���X

};

