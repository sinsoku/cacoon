#include "stdafx.h"
#include "HttpClient.h"
#include "OAuthHandler.h"

// URL エンコーディング
TEST( OAuthTest, UrlEncoging )
{
	const std::string source = "https://auth.login.yahoo.co.jp/oauth/v2/get_request_token";
	const std::string expect = "https%3A%2F%2Fauth.login.yahoo.co.jp%2Foauth%2Fv2%2Fget_request_token";

	const std::string urlEnc = OAuthHandler::UrlEncode( source );

	EXPECT_EQ( expect, urlEnc );
}

// OpenSSL HMAC-SHA1 + Base64 エンコーディング
TEST( OAuthTest, HmacSha1Base64 )
{
	size_t resLength;
	unsigned char res[SHA_DIGEST_LENGTH + 1];

	char key[] = "1";
	int keyLength = strlen( key );

	unsigned char data[] = "012345";
	size_t dataLength = sizeof( data ) - 1;

	HMAC( EVP_sha1(), key, keyLength, data, dataLength, res, &resLength );

	char b64[256];
	DWORD b64Length;

	CryptBinaryToStringA( res, resLength, CRYPT_STRING_BASE64, b64, &b64Length );

	// 変換した文字列の最後に CRLF がついてくるのでそれをとる。
	char b64withoutCRLF[256];
	int b64length = strlen( b64 );
	for( int i=0; i<b64length-2; i++ )	// CRLF 分が -2
	{
		b64withoutCRLF[i] = b64[i];
	}
	b64withoutCRLF[b64length-2] = 0;	// null 文字
	std::cout << b64withoutCRLF << std::endl;
	
	// Python で作った値と比較。
	EXPECT_STREQ( "uSAq0a63u1W41eTdCrgbywm5CU8=", b64withoutCRLF );
}

// OpenSSL HMAC-SHA1 のテスト
TEST( OAuthTest, HmacSha1 )
{
	size_t resLength;
	unsigned char res[SHA_DIGEST_LENGTH + 1];

	char key[] = "1";
	int keyLength = strlen( key );

	unsigned char data[] = "012345";
	size_t dataLength = sizeof( data ) - 1;

	HMAC( EVP_sha1(), key, keyLength, data, dataLength, res, &resLength );

	std::ostringstream oss;

	for( int i=0; i<(int)sizeof( res ) - 1; i++ )
	{
		oss << boost::format( "%02x" ) % (int)res[i];
	}

	std::cout << oss.str() << std::endl;
	
	// Python で作った場合と比較
	EXPECT_STREQ( "b9202ad1aeb7bb55b8d5e4dd0ab81bcb09b9094f", oss.str().c_str() );
}