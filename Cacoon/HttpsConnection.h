#pragma once
#include "ConnectionImpl.h"
#include "SocketConnector.h"

class HttpsConnection : public ConnectionImpl
{
public:
	explicit HttpsConnection( const std::string & host );
	~HttpsConnection();

protected:
	// ConnectionImpl からのオーバーライド
	void makeConnection();
	void sendRequest( const std::string & request );
	int receive( char * buf, int bufferSize );
	
private:
	SocketConnector sock;
	SSL_CTX * ctx;
	SSL * ssl;

};

