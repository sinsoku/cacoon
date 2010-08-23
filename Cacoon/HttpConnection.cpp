#include "stdafx.h"
#include "HttpConnection.h"

HttpConnection::HttpConnection( const std::string & hostname )
	: host( hostname )
{
	this->sock = socket( AF_INET, SOCK_STREAM, 0 );

	if( sock == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "ソケット初期化エラー" );
	}

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );
	server.sin_addr.S_un.S_addr = inet_addr( hostname.c_str() );
	if( server.sin_addr.S_un.S_addr == 0xFFFFFFFF )
	{	// host が文字列の場合
		hostent * host = gethostbyname( hostname.c_str() );
		if( host == NULL )
		{
			throw CACOON_EXCEPTION( "不明なホスト名" );
		}

		unsigned int ** addressList = (unsigned int **)host->h_addr_list;

		while( *addressList != NULL )
		{
			server.sin_addr.S_un.S_addr = **addressList;

			if( connect( sock, (sockaddr *)&server, sizeof( server ) ) == 0 )
			{	// connect が成功したらループを抜ける
				break;
			}
			else
			{	// 次のアドレスをさす
				addressList++;
			}
		}
		if( *addressList == NULL )
		{	// connect がすべて失敗した場合
			throw CACOON_EXCEPTION( "connect に失敗" );
		}
	}
	else
	{	// host が数字列の場合
		if( connect( sock, (sockaddr *)&server, sizeof( server ) ) != 0 )
		{
			throw CACOON_EXCEPTION( "connect に失敗" );
		}
	}
}


HttpConnection::~HttpConnection()
{
	closesocket( this->sock );
}

Response HttpConnection::Request( const std::string & method, const std::string & url, const std::string & header )
{
	std::ostringstream ossReq( std::ios::binary );
	ossReq << method << " " << url << " HTTP/1.1\r\nHost: " << this->host << "\r\n\r\n" << '\0';

	// HTTP リクエスト送信
	int n = send( this->sock, ossReq.str().c_str(), ossReq.str().length(), 0 );
	if( n < 0 )
	{
		throw CACOON_EXCEPTION( "send エラー" );
	}

	std::ostringstream ossResult( std::ios::binary );

	const int BufferSize = 256;
	char buf[BufferSize];

	// サーバからの HTTP メッセージ受信
	while( n == BufferSize	 )
	{
		memset( buf, 0, BufferSize );
		n = recv( this->sock, buf, BufferSize, 0 );
		if( n < 0 )
		{
			throw CACOON_EXCEPTION( "recv エラー" );
		}
		// 受信結果
		ossResult.write( buf, BufferSize );
	}
	return Response( ossResult.str() );
}