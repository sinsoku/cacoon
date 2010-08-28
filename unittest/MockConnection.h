#pragma once
#include "ConnectionImpl.h"

class MockConnection : public ConnectionImpl
{
public:
	explicit MockConnection( const std::string & host );
	~MockConnection();

	// ConnectionImpl からのオーバーライド
	Response Request( const std::string & method, const std::string & url, const HeaderMap & header );

private:
	std::string host;
};

