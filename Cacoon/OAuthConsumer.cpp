#include "StdAfx.h"
#include "OAuthConsumer.h"

OAuthConsumer::OAuthConsumer()
	: Key( "" )
	, Secret( "" )
{
}

OAuthConsumer::OAuthConsumer( const std::string & key, const std::string & secret )
	: Key( key )
	, Secret( secret )
{
}