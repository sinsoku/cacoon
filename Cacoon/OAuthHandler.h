#pragma once
#include "cacoohandler.h"
#include "OAuthUrlMaker.h"

class OAuthHandler : public CacooHandler
{
public:
	OAuthHandler( const std::string & consumerKey, const std::string & consumerSecret, const std::string & accessKey, const std::string & accessSecret );
	virtual ~OAuthHandler();

	// CacooHandler からのオーバーライド
	std::string get( const std::string & url );

private:
	OAuthUrlMaker oauthUrlMaker;
};

