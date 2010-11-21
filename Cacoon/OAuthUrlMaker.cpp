#include "StdAfx.h"
#include "OAuthUrlMaker.h"
#include "OAuthRequest.h"
#include "HttpClient.h"

OAuthUrlMaker::OAuthUrlMaker( const std::string & consumerKey, const std::string & consumerSecret )
	: consumer( consumerKey, consumerSecret )
	, host( "cacoo.com" )
	, root( "/oauth/" )
	, secure( true )
{
}

void OAuthUrlMaker::SetOAuthUrl( const std::string & host, const std::string & root, bool secure )
{
	this->host = host;
	this->root = root;
	this->secure = secure;
}

std::string OAuthUrlMaker::GetOAuthUrl( const std::string & endpoint )
{
	std::string prefix = (this->IsSecure()) ? "https://" : "http://";

	return prefix + this->host + this->root + endpoint;
}

void OAuthUrlMaker::SetAccessToken( const std::string & accessKey, const std::string & accessSecret )
{
	this->access = OAuthToken( accessKey, accessSecret );
}

std::string OAuthUrlMaker::OAuthHost()
{
	return this->host;
}

std::string OAuthUrlMaker::OAuthRoot()
{
	return this->root;
}

bool OAuthUrlMaker::IsSecure()
{
	return this->secure;
}

OAuthToken OAuthUrlMaker::getRequestToken()
{
	OAuthRequest request( this->consumer, this->GetOAuthUrl( "request_token" ) );
	request.SignRequest();
	HeaderMap hm( request.ToHeaderString() );
	
	Connection conn = HttpClient::CreateHttpsConnection( this->host );
	Response resp = conn.Request( "POST", this->root + "request_token", hm );

	return OAuthToken::FromString( resp.Body() );
}

std::string OAuthUrlMaker::GetAuthorizationUrl( const std::string & endpoint )
{
	this->request = OAuthUrlMaker::getRequestToken();
	return this->GetOAuthUrl( endpoint ) + "?oauth_token=" + this->request.Key;
}

OAuthToken OAuthUrlMaker::GetAccessToken( const std::string & verifier )
{
	OAuthRequest request( this->consumer, this->request, this->GetOAuthUrl( "access_token" ), verifier );
	request.SignRequest();
	HeaderMap hm( request.ToHeaderString() );

	Connection conn = HttpClient::CreateHttpsConnection( this->host );
	Response resp = conn.Request( "POST", this->root + "access_token", hm );
	
	return OAuthToken::FromString( resp.Body() );
}

std::string OAuthUrlMaker::MakeAuthorizationHeader( const std::string & method, const std::string & url )
{
	if( this->access.Key == "" || this->access.Secret == "" )
	{
		throw CACOON_EXCEPTION( "アクセストークンがありません" );
	}
	OAuthRequest request( this->consumer, this->access, url, "", method );
	request.SignRequest();

	return request.ToHeaderString();
}