#pragma once
#include "OAuthConsumer.h"
#include "OAuthToken.h"

class OAuthHandler
{
public:

	OAuthHandler( const std::string & consumerKey, const std::string & consumerSecret );

	void SetOAuthUrl( const std::string & host, const std::string & root, bool secure );
	std::string GetOAuthUrl( const std::string & url = "" );

	std::string OAuthHost();
	std::string OAuthRoot();
	bool IsSecure();
	
	OAuthToken GetRequestToken();
	OAuthToken GetAccessToken();

	static std::string UrlEncode( const std::string & source );
	static std::string HmacSha1WithBase64Encode( const std::string & source, const std::string & key );

private:

	std::string host;
	std::string root;
	bool secure;

	OAuthConsumer consumer;
	OAuthToken access;
	OAuthToken request;

	static std::basic_string<unsigned char> stringToByteString( const std::string & source );
	static std::string GenerateTimeStamp();
	static std::string GenerateNonce( int length = 8 );
};

