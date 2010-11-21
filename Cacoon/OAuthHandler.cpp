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
	int prefixLength = url.find( "://" ) + 3;	// "https://" ÇÃí∑Ç≥
	int rootLength = url.substr( prefixLength ).find( "/" );
	std::string root = url.substr( prefixLength, rootLength );	// "https://(xxxx)/**" ÇÃ (xxxx) Çíäèo
	std::string endpoint = url.substr( prefixLength + rootLength );	// è„ÇÃ (xxxx) à»ç~Çíäèo
	
	static std::string authHeader = this->oauthUrlMaker.MakeAuthorizationHeader( "GET", url );

	Connection conn = HttpClient::CreateHttpsConnection( root );
	Response resp = conn.Request( "GET", endpoint, HeaderMap( authHeader ) );

	if( resp.StatusCode() != 200 )
	{
		throw CACOON_EXCEPTION( "OAuth Ç…ÇÊÇÈê⁄ë±Ç…é∏îs" );
	}

	return resp.Body();
}