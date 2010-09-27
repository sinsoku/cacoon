#pragma once
struct OAuthToken
{
	std::string Key;
	std::string Secret;

	OAuthToken();
	OAuthToken( const std::string & key, const std::string & secret );

	std::string ToString();

	static OAuthToken FromString( const std::string & str );
};

