#pragma once
#include "ConnectionImpl.h"
class MockConnection : public ConnectionImpl
{
public:
	MockConnection( const std::string & host );
	~MockConnection();

	// ConnectionImpl ����̃I�[�o�[���C�h
	Response Request( const std::string & method, const std::string & url, const std::string & header );

private:
	std::string host;
};

