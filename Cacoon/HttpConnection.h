#pragma once
#include "ConnectionImpl.h"
#include "SocketConnector.h"

class HttpConnection : public ConnectionImpl
{
public:
	explicit HttpConnection( const std::string & host );
	~HttpConnection();

	// ConnectionImpl ����̃I�[�o�[���C�h
	Response Request( const std::string & method, const std::string & url, const HeaderMap & header );

private:
	SocketConnector sock;
	const std::string host;
};

