#pragma once
#include "ConnectionImpl.h"

class HttpConnection : public ConnectionImpl
{
public:
	HttpConnection( const std::string & host );
	~HttpConnection();

	// ConnectionImpl ����̃I�[�o�[���C�h
	Response Request( const std::string & method, const std::string & url, const std::string & header );

private:
	SOCKET sock;
	const std::string host;
};

