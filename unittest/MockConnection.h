#pragma once
#include "ConnectionImpl.h"

class MockConnection : public ConnectionImpl
{
public:
	explicit MockConnection( const std::string & host );

	// ConnectionImpl からのオーバーライド
	Response Request( const std::string & method, const std::string & url, const HeaderMap & header );

protected:
	
	// ConnectionImpl からのオーバーライド
	void makeConnection() {}
	void sendRequest( const std::string & request ) {}
	int receive( char * buf, int bufferSize ) { return 0; }

};

