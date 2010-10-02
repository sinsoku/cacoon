#include "StdAfx.h"
#include "OAuthRequest.h"

OAuthRequest::OAuthRequest( const OAuthConsumer & consumer, const std::string & requestTokenUrl, const std::string & method )
	: consumer( consumer )
	, url( requestTokenUrl )
	, method( method )
	, params( OAuthRequest::makeDefaultParams( consumer ) )
{
}

OAuthRequest::OAuthRequest( const OAuthConsumer & consumer, const OAuthToken & token, const std::string & url, const std::string & verifier, const std::string & method )
	: consumer( consumer )
	, token( token )
	, verifier( verifier )
	, url( url )
	, method( method )
	, params( OAuthRequest::makeDefaultParams( consumer ) )
{
	params["oauth_token"] = this->token.Key;
	if( verifier != "" )
	{
		params["oauth_verifier"] = verifier;
	}
}


std::map<std::string, std::string> OAuthRequest::makeDefaultParams( const OAuthConsumer & consumer )
{
	std::map<std::string, std::string> result;
	result["oauth_consumer_key"] = consumer.Key;
	result["oauth_timestamp"] = OAuthRequest::generateTimeStamp();
	result["oauth_nonce"] = OAuthRequest::generateNonce();
	result["oauth_signature_method"] = "HMAC-SHA1";
	result["oauth_version"] = "1.0";
	result["oauth_callback"] = "oob";

	return result;
}

void OAuthRequest::SignRequest()
{
	std::ostringstream oss;
	std::map<std::string, std::string>::iterator it = this->params.begin();

	oss << it->first << '=' << it->second;
	it++;
	for( ; it != this->params.end(); it++ )
	{
		oss << '&' << it->first << '=' << it->second;
	}

	std::string encodedMethod = OAuthRequest::UrlEncode( this->method );
	std::string encodedUrl = OAuthRequest::UrlEncode( this->url );
	std::string encodedParams = OAuthRequest::UrlEncode( oss.str() );

	std::string signSource = encodedMethod + '&' + encodedUrl + '&' + encodedParams;
	std::string signKey = this->consumer.Secret + '&' + this->token.Secret;

	std::string signature = OAuthRequest::HmacSha1WithBase64Encode( signSource, signKey );

	this->params["oauth_signature"] = signature;
}

std::string OAuthRequest::ToHeaderString()
{
	std::ostringstream oss;
	std::map<std::string, std::string>::iterator it = this->params.begin();
	oss << "Authorization: OAuth " << it->first << "=\"" << OAuthRequest::UrlEncode( it->second ) << "\"";
	it++;
	for( ; it != this->params.end(); it++ )
	{
		oss << "," << it->first << "=\"" << it->second << "\"";
	}
	return oss.str();
}

// タイムスタンプを生成
std::string OAuthRequest::generateTimeStamp()
{
	return boost::lexical_cast<std::string>( (int)time( NULL ) );
}

// oauth_nonce に必要なランダムな文字列を生成
std::string OAuthRequest::generateNonce( int length )
{
	static time_t t = time( NULL );
	srand( t++ );
	std::vector<char> v;
	for( int i=0; i<length; i++ )
	{
		v.push_back( (char)(rand()%10 + 0x30) ); // means itoa
	}
	v.push_back( '\0' );
	return std::string( &v[0] );
}

std::string OAuthRequest::UrlEncode( const std::string & source )
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
		{	// [0-9], [A-Z], [a-z]、[.], [-], [_] のときはそのまま出力
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

std::string OAuthRequest::HmacSha1WithBase64Encode( const std::string & source, const std::string & key )
{
	size_t hashedLength;
	unsigned char hashed[SHA_DIGEST_LENGTH + 1];

	std::basic_string<unsigned char> sourceAsByte = OAuthRequest::stringToByteString( source );

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
std::basic_string<unsigned char> OAuthRequest::stringToByteString( const std::string & source )
{
	std::basic_string<unsigned char> result;
	result.resize( source.length() );

	for( int i=0; i<(int)source.length(); i++ )
	{
		result[i] = (unsigned char)source[i];
	}
	
	return result;
}