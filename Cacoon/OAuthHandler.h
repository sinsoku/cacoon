#pragma once
class OAuthHandler
{
public:
	OAuthHandler();
	~OAuthHandler();

	static std::string UrlEncode( const std::string & source );
	static std::string HmacSha1WithBase64Encode( const std::string & source, const std::string & key );

private:
	static std::basic_string<unsigned char> stringToByteString( const std::string & source );
};

