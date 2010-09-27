#pragma once
struct OAuthConsumer
{
	std::string Key;
	std::string Secret;

	OAuthConsumer();
	OAuthConsumer( const std::string & key, const std::string & secret );
};

