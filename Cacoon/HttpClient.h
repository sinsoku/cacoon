#pragma once
#include "stdafx.h"
#include "Connection.h"

struct WSAData;
// HTTP や HTTPS による接続を作成するためのファクトリークラス
class HttpClient
{
public:
	static Connection CreateHttpConnection( const std::string & host );
	static Connection CreateHttpsConnection( const std::string & host );

	// URL に簡単にアクセスするための静的メソッド
	static Response Connect( const std::string & method, const std::string & url, const HeaderMap & header = HeaderMap() );
	
	~HttpClient();

private:

	HttpClient();	// 作成禁止
	WSAData * data;
	static HttpClient httpClient;	// 唯一のインスタンス

};

