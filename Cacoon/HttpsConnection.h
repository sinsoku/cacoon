#pragma once
#include "ConnectionImpl.h"
#include "SocketConnector.h"

class HttpsConnection : public ConnectionImpl
{
public:
	explicit HttpsConnection( const std::string & host );
	~HttpsConnection();

	// ConnectionImpl からのオーバーライド
	Response Request( const std::string & method, const std::string & url, const HeaderMap & header );
	
private:
	SocketConnector sock;
	SSL_CTX * ctx;
	SSL * ssl;
	const std::string host;

	// SSL コネクションの確立
	void makeSslConnection();
};

