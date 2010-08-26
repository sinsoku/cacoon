#include "StdAfx.h"
#include "Connection.h"
#include "ConnectionImpl.h"

Connection::Connection( ConnectionImpl * pConnection )
	: pImpl( pConnection )
{
}

Response Connection::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	return this->pImpl->Request( method, url, header );
}