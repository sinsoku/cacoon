#include "stdafx.h"
#include "HttpConnection.h"
#include "HeaderMap.h"

HttpConnection::HttpConnection( const std::string & host )
	: ConnectionImpl( host )
	, sock( host, 80 )
{
}

void HttpConnection::makeConnection()
{
	this->sock.Connect();
}

void HttpConnection::sendRequest( const std::string & request )
{
	int n = send( this->sock.Socket(), request.c_str(), request.length(), 0 );
	if( n < 0 )
	{
		throw CACOON_EXCEPTION( "send ƒGƒ‰[" );
	}
}

int HttpConnection::receive( char * buf, int bufferSize )
{
	memset( buf, 0, bufferSize );
	return recv( this->sock.Socket(), buf, bufferSize, 0 );
}