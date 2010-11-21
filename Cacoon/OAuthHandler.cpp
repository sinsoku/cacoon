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
	int prefixLength = url.find( "://" ) + 3;	// "https://" の長さ
	int rootLength = url.substr( prefixLength ).find( "/" );
	std::string root = url.substr( prefixLength, rootLength );	// "https://(xxxx)/**" の (xxxx) を抽出
	std::string endpoint = url.substr( prefixLength + rootLength );	// 上の (xxxx) 以降を抽出
	
	static std::string authHeader = this->oauthUrlMaker.MakeAuthorizationHeader( "GET", url );

	Connection conn = HttpClient::CreateHttpsConnection( root );
	Response resp = conn.Request( "GET", endpoint, HeaderMap( authHeader ) );

	if( resp.StatusCode() != 200 )
	{
		throw CACOON_EXCEPTION( "OAuth による接続に失敗" );
	}

	return resp.Body();
}