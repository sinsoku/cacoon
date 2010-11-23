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
	std::string authHeader = this->oauthUrlMaker.MakeAuthorizationHeader( Method::Get, url );
	Response resp = HttpClient::Connect( Method::Get, url, HeaderMap( authHeader ) );

	if( resp.StatusCode() != 200 )
	{
		throw CACOON_EXCEPTION( "OAuth ‚É‚æ‚éÚ‘±‚É¸”s" );
	}

	return resp.Body();
}