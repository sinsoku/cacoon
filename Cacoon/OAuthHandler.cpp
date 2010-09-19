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

std::string OAuthHandler::HmacSha1WithBase64Encode( const std::string & source, const std::string & key )
{
	size_t hashedLength;
	unsigned char hashed[SHA_DIGEST_LENGTH + 1];

	std::basic_string<unsigned char> sourceAsByte = OAuthHandler::stringToByteString( source );

	HMAC( EVP_sha1(), key.c_str(), key.length(), sourceAsByte.c_str(), source.length(), hashed, &hashedLength );
	
	DWORD b64Length;

	// まずサイズを計算する。
	CryptBinaryToStringA( hashed, hashedLength, CRYPT_STRING_BASE64, NULL, &b64Length );

	char * resultCStr = new char[b64Length];

	// 実際に変換
	CryptBinaryToStringA( hashed, hashedLength, CRYPT_STRING_BASE64, resultCStr, &b64Length );

	std::string result( resultCStr );

	delete resultCStr;
	
	// 変換した文字列の最後に CRLF がついてくるのでそれをとる。
	return result.substr( 0, result.length() - 2 );
}

// string を Byte 配列にキャストする。
std::basic_string<unsigned char> OAuthHandler::stringToByteString( const std::string & source )
{
	std::basic_string<unsigned char> result;
	result.resize( source.length() );

	for( int i=0; i<(int)source.length(); i++ )
	{
		result[i] = (unsigned char)source[i];
	}
	
	return result;
}