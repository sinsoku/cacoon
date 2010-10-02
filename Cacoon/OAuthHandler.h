#pragma once
#include "OAuthConsumer.h"
#include "OAuthToken.h"

class OAuthHandler
{
public:

	OAuthHandler( const std::string & consumerKey, const std::string & consumerSecret );

	void SetOAuthUrl( const std::string & host, const std::string & root, bool secure );
	std::string GetOAuthUrl( const std::string & endpoint = "" );

	void SetAccessToken( const std::string & accessKey, const std::string & accessSecret );
	OAuthToken GetAccessToken( const std::string & verifier );

	std::string OAuthHost();
	std::string OAuthRoot();
	bool IsSecure();
	
	std::string GetAuthorizationUrl( const std::string & endpoint = "authorize" );

	std::string MakeAuthorizationHeader( const std::string & method, const std::string & url );

private:

	std::string host;
	std::string root;
	bool secure;

	OAuthConsumer consumer;
	OAuthToken request;
	OAuthToken access;

	OAuthToken getRequestToken();

	OAuthHandler( const OAuthHandler & );
	OAuthHandler & operator = ( const OAuthHandler & );
};

