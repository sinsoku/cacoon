#include "StdAfx.h"
#include "HttpsConnection.h"


HttpsConnection::HttpsConnection( const std::string & host )
{
}

HttpsConnection::~HttpsConnection()
{
}

Response HttpsConnection::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	// TODO: Not Implemented yet.
	throw CACOON_EXCEPTION( "Not implemented yet" );
}