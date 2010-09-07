#include "StdAfx.h"
#include "OAuthHandler.h"


OAuthHandler::OAuthHandler()
{
}


OAuthHandler::~OAuthHandler()
{
}

std::string OAuthHandler::UrlEncode( const std::string & source )
{
	const char WhiteSpace = ' ';
	const char Period = '.';
	const char Minus = '-';
	const char UnderBar = '_';

	std::ostringstream oss;

	BOOST_FOREACH( const char &c, source )
	{
		if( isalnum( c )
		 || c == Period
		 || c == Minus
		 || c == UnderBar )
		{	// [0-9], [A-Z], [a-z]、[.], [_], [-] のときはそのまま出力
			oss << c;
		}
		else if( c == WhiteSpace )
		{	// 半角スペースは + に変換
			oss << '+';
		}
		else
		{	// そのほかは [%16進] 出力
			oss << '%' << std::hex << std::uppercase << (int)c;
		}
	}

	return oss.str();
}
