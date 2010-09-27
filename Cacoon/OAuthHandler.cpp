#include "StdAfx.h"
#include "OAuthHandler.h"
#include "HttpClient.h"

OAuthHandler::OAuthHandler( const std::string & consumerKey, const std::string & consumerSecret )
	: consumer( consumerKey, consumerSecret )
{
}

void OAuthHandler::SetOAuthUrl( const std::string & host, const std::string & root, bool secure )
{
	this->host = host;
	this->root = root;
	this->secure = secure;
}

std::string OAuthHandler::GetOAuthUrl( const std::string & url )
{
	std::string prefix = (this->IsSecure()) ? "https://" : "http://";

	return prefix + this->host + this->root + url;
}

std::string OAuthHandler::OAuthHost()
{
	return this->host;
}

std::string OAuthHandler::OAuthRoot()
{
	return this->root;
}

bool OAuthHandler::IsSecure()
{
	return this->secure;
}

OAuthToken OAuthHandler::GetRequestToken()
{
	std::map<std::string, std::string> oauthParam;
	oauthParam["oauth_consumer_key"] = consumer.Key;
	oauthParam["oauth_timestamp"] = OAuthHandler::GenerateTimeStamp();
	oauthParam["oauth_nonce"] = OAuthHandler::GenerateNonce();
	oauthParam["oauth_signature_method"] = "HMAC-SHA1";
	oauthParam["oauth_version"] = "1.0";
	oauthParam["oauth_callback"] = "oob";

	std::ostringstream baseOss;
	for( std::map<std::string, std::string>::iterator it = oauthParam.begin(); it != oauthParam.end(); it++ )
	{
		baseOss << it->first << '=' << it->second << '&';
	}

	std::string ps = baseOss.str();
	ps.pop_back();
	std::string paramsString = OAuthHandler::UrlEncode( ps );
	std::string methodString = OAuthHandler::UrlEncode( "POST" );
	std::string accessString = OAuthHandler::UrlEncode( this->GetOAuthUrl( "request_token" ) );

	std::string targetString = methodString + '&' + accessString + '&' + paramsString;
	
	std::string keyString = OAuthHandler::UrlEncode( this->consumer.Secret ) + '&';

	std::string signature = OAuthHandler::HmacSha1WithBase64Encode( targetString, keyString );

	oauthParam["oauth_signature"] = OAuthHandler::UrlEncode( signature );
	std::ostringstream postOss;
	postOss << "OAuth ";
	for( std::map<std::string, std::string>::iterator it = oauthParam.begin(); it != oauthParam.end(); it++ )
	{
		postOss << it->first << "=\"" << it->second << "\",";
	}
	std::string postString = postOss.str();
	postString.pop_back();

	HeaderMap hm;
	hm.Insert( "Authorization", postString );

	Connection conn = HttpClient::CreateHttpsConnection( this->host );
	Response resp = conn.Request( "POST", this->root + "request_token", hm );

	return OAuthToken( "", "" );
}

OAuthToken OAuthHandler::GetAccessToken()
{
	return OAuthToken( "", "" );
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

// タイムスタンプを生成
std::string OAuthHandler::GenerateTimeStamp()
{
	return boost::lexical_cast<std::string>( (int)time( NULL ) );
}

// oauth_nonce に必要なランダムな文字列を生成
std::string OAuthHandler::GenerateNonce( int length )
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