#include "stdafx.h"
#include "HttpClient.h"
#include "HttpConnection.h"
#include "HttpsConnection.h"

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

// URL に簡単にアクセスするための静的メソッド
Response HttpClient::Connect( const std::string & method, const std::string & url, const HeaderMap & header )
{
	int prefixLength = url.find( "://" ) + 3;	// "https://" の長さ
	int rootLength = url.substr( prefixLength ).find( "/" );
	std::string root = url.substr( prefixLength, rootLength );	// "https://(xxxx)/**" の (xxxx) を抽出
	std::string endpoint = url.substr( prefixLength + rootLength );	// 上の (xxxx) 以降を抽出

	Connection conn = ( url.substr( 0, 5 ) == "https" )
		? HttpClient::CreateHttpsConnection( root )
		: HttpClient::CreateHttpConnection( root );

	return conn.Request( "GET", endpoint, header );
}
