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
	typedef boost::char_separator<char> Separator;
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	Separator andSeparator( "&" );
	Tokenizer keyAndValue( str, andSeparator );

	Separator equalSeparator( "=" );
	std::map<std::string, std::string> m;
	BOOST_FOREACH( const std::string & s, keyAndValue )
	{
		Tokenizer keyOrValue( s, equalSeparator );
		Tokenizer::iterator it = keyOrValue.begin();

		m[*it++] = *it;
	}

	return OAuthToken( m["oauth_token"], m["oauth_token_secret"] );
}