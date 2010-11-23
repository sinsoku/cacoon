#pragma once
#include "ConnectionImpl.h"
#include "SocketConnector.h"

class HttpConnection : public ConnectionImpl
{
public:
	explicit HttpConnection( const std::string & host );
	
protected:
	// ConnectionImpl ����̃I�[�o�[���C�h
	void makeConnection();
	void sendRequest( const std::string & request );
	int receive( char * buf, int bufferSize );

private:

	SocketConnector sock;
};

