#include "StdAfx.h"
#include "OAuthHandler.h"
#include "HttpClient.h"

OAuthHandler::OAuthHandler( const std::string & consumerKey, const std::string & consumerSecret, const std::string & accessKey, const std::string & accessSecret )
	: oauthUrlMaker( consumerKey, consumerSecret )
{
	this->oauthUrlMaker.SetAccessToken( accessKey, accessSecret );
}

OAuthHandler::~OAuthHandler()
{
}

std::string OAuthHandler::get( const std::string & url )
{
	int prefixLength = url.find( "://" ) + 3;	// "https://" ‚Ì’·‚³
	int rootLength = url.substr( prefixLength ).find( "/" );
	std::string root = url.substr( prefixLength, rootLength );	// "https://(xxxx)/**" ‚Ì (xxxx) ‚ğ’Šo
	std::string endpoint = url.substr( prefixLength + rootLength );	// ã‚Ì (xxxx) ˆÈ~‚ğ’Šo

	Connection conn = HttpClient::CreateHttpsConnection( root );
	
	std::string authHeader = this->oauthUrlMaker.MakeAuthorizationHeader( "GET", url );
	Response resp = conn.Request( "GET", endpoint, HeaderMap( authHeader ) );

	if( resp.StatusCode() != 200 )
	{
		throw CACOON_EXCEPTION( "OAuth ‚É‚æ‚éÚ‘±‚É¸”s" );
	}

	return resp.Body();
}