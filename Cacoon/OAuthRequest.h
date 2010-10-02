#pragma once
#include "OAuthConsumer.h"
#include "OAuthToken.h"

class OAuthRequest
{
public:

	OAuthRequest( const OAuthConsumer & consumer, const std::string & requestTokenUrl, const std::string & method = "POST" );
	OAuthRequest( const OAuthConsumer & consumer, const OAuthToken & token, const std::string & url, const std::string & verifier = "", const std::string & method = "POST" );

	void SignRequest();
	std::string ToHeaderString();

	static std::string UrlEncode( const std::string & source );
	static std::string HmacSha1WithBase64Encode( const std::string & source, const std::string & key );

private:
	
	static std::map<std::string, std::string> makeDefaultParams( const OAuthConsumer & consumer );
	static std::string generateTimeStamp();
	static std::string generateNonce( int length = 8 );
	static std::basic_string<unsigned char> stringToByteString( const std::string & source );

	const OAuthConsumer consumer;
	const OAuthToken token;
	const std::string verifier;
	const std::string url;
	const std::string method;
	std::map<std::string, std::string> params;

	OAuthRequest( const OAuthRequest & );
	OAuthRequest & operator = ( const OAuthRequest & );
};

