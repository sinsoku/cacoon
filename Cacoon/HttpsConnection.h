#pragma once
#include "ConnectionImpl.h"

class HttpsConnection : public ConnectionImpl
{
public:
	HttpsConnection( const std::string & host );
	~HttpsConnection();

	// ConnectionImpl ����̃I�[�o�[���C�h
	Response Request( const std::string & method, const std::string & url, const std::string & header );
};

