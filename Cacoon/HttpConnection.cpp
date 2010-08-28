#include "stdafx.h"
#include "HttpConnection.h"

HttpConnection::HttpConnection( const std::string & hostname )
	: host( hostname )
{
	this->sock = ConnectionImpl::MakeSocket();
	this->addr = ConnectionImpl::MakeAddressFamily( this->sock, hostname, 80 );
	closesocket( this->sock );
}


HttpConnection::~HttpConnection()
{
}

Response HttpConnection::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	if( header.IsKeyExists( "Host" ) )
	{
		throw CACOON_EXCEPTION( "Host ヘッダは必要ありません。" );
	}
	if( header.IsKeyExists( "Connection" ) )
	{
		throw CACOON_EXCEPTION( "Connection ヘッダは現時点では対応していません。" );
	}
	std::ostringstream ossReq( std::ios::binary ); // \r\n を正しく処理するためバイナリとする。
	ossReq << method << " " << url << " HTTP/1.1\r\n"
		"Host: " << this->host << "\r\n"
		"Connection: close\r\n"
		<< header.ToString() << "\r\n" << '\0';

	// コネクション確立
	this->sock = ConnectionImpl::MakeSocket();
	ConnectionImpl::Connect( this->sock, this->addr );
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
	while( n > 0 )
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