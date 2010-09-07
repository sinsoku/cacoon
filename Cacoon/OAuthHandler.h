#pragma once
class OAuthHandler
{
public:
	OAuthHandler();
	~OAuthHandler();

	static std::string UrlEncode( const std::string & source );
};

