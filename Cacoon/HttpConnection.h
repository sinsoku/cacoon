#pragma once
#include "ConnectionImpl.h"
#include "SocketConnector.h"

class HttpConnection : public ConnectionImpl
{
public:
	explicit HttpConnection( const std::string & host );
	
protected:
	// ConnectionImpl からのオーバーライド
	void makeConnection();
	void sendRequest( const std::string & request );
	int receive( char * buf, int bufferSize );

private:

	SocketConnector sock;
};

