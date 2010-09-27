#include "StdAfx.h"
#include "OAuthToken.h"


OAuthToken::OAuthToken()
	: Key( "" )
	, Secret( "" )
{
}

OAuthToken::OAuthToken( const std::string & key, const std::string & secret )
	: Key( key )
	, Secret( secret )
{
}

std::string OAuthToken::ToString()
{
	return "";
}

OAuthToken OAuthToken::FromString( const std::string & str )
{
	return OAuthToken();
}