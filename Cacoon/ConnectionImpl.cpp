#include "stdafx.h"
#include "HeaderMap.h"
#include "ConnectionImpl.h"

ConnectionImpl::ConnectionImpl( const std::string & host )
	: HostName( host )
{
}

Response ConnectionImpl::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	HeaderMap hm( header );
	if( !hm.IsKeyExists( "Host" ) )
	{
		hm.Insert( "Host", this->HostName );
	}
	if( !hm.IsKeyExists( "Connection" ) )
	{
		hm.Insert( "Connection", "close" );
	}
	std::ostringstream ossReq( std::ios::binary ); // \r\n を正しく処理するためバイナリとする。
	ossReq << method << " " << url << " HTTP/1.1\r\n" << hm.ToString() << "\r\n" << '\0';

	this->makeConnection();
	this->sendRequest( ossReq.str() );

	std::ostringstream ossResult( std::ios::binary );

	const int BufferSize = 256;
	char buf[BufferSize];

	// サーバから受信
	while( 1 )
	{
		int readSize = this->receive( buf, BufferSize );
		if( readSize > 0 )
		{
			ossResult.write( buf, readSize );
		}
		else if( readSize == 0 )
		{
			break;
		}
		else
		{
			throw CACOON_EXCEPTION( "recv エラー" );
		}
	}
	return Response( ossResult.str() );
}