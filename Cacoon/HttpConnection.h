#pragma once
#include "ConnectionImpl.h"
#include "HeaderMap.h"

class HttpConnection : public ConnectionImpl
{
public:
	explicit HttpConnection( const std::string & host );
	~HttpConnection();

	// ConnectionImpl からのオーバーライド
	Response Request( const std::string & method, const std::string & url, const HeaderMap & header );

private:
	SOCKET sock;
	SOCKADDR_IN addr;
	const std::string host;
};

