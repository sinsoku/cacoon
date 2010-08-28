#include "stdafx.h"
#include "HttpClient.h"
#include "HttpConnection.h"
#include "HttpsConnection.h"
#include "MockConnection.h"

HttpClient HttpClient::httpClient;	// 唯一のインスタンス (ここで自動的にコンストラクタが呼ばれる)

// プログラムの初期化時に呼ばれる
HttpClient::HttpClient()
{
	this->data = new WSAData();
	WSAStartup( MAKEWORD( 2, 0 ), this->data );
}

// プログラムの終了時に呼ばれる
HttpClient::~HttpClient()
{
	WSACleanup();
	delete this->data;
}

// HTTP 接続クラスの作成
Connection HttpClient::CreateHttpConnection( const std::string & host )
{
	return Connection( new HttpConnection( host ) );
}

// HTTPS 接続クラスの作成
Connection HttpClient::CreateHttpsConnection( const std::string & host )
{
	return Connection( new HttpsConnection( host ) );
}