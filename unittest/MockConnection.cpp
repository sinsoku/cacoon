#include "StdAfx.h"
#include "MockConnection.h"


MockConnection::MockConnection( const std::string & host )
	: ConnectionImpl( host )
{
}

Response MockConnection::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	std::string mockResponse = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Last-Modified: Sun, 25 Jul 2010 03:44:38 GMT\r\n"
"Accept-Ranges: bytes\r\n"
"ETag: \"f7b3acb4ab2bcb1:0\"\r\n"
"Server: Microsoft-IIS/7.5\r\n"
"X-Powered-By: ASP.NET\r\n"
"Date: Wed, 18 Aug 2010 13:28:20 GMT\r\n"
"Connection: close\r\n"
"Content-Length: 9415\r\n"
"\r\n"
"This is a test string\r\n";

	return Response( mockResponse );
}