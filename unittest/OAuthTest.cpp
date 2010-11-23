#include "stdafx.h"
#include "HttpClient.h"
#include "OAuthRequest.h"
#include "OAuthUrlMaker.h"
// URL �̐ݒ�A�擾
TEST( OAuthTest, OAuthUrl )
{
	OAuthUrlMaker oauth( "", "" );
	oauth.SetOAuthUrl( "cacoo.com", "/oauth/", true );

	EXPECT_EQ( std::string( "https://cacoo.com/oauth/request_token" ), oauth.GetOAuthUrl( "request_token" ) );
}

// OAuth �̏����쐬
TEST( OAuthTest, OAuthSignature )
{
	const std::string source = "GET&https%3A%2F%2Fauth.login.yahoo.co.jp%2Foauth%2Fv2%2Fget_request_token&oauth_callback%3Dhttp%253A%252F%252Fwww.example.com%252F%26oauth_consumer_key%3Dtest_consumer_key%26oauth_nonce%3D3a1f92580ea537395b42d2d1cdf5fe29%26oauth_signature_method%3DHMAC-SHA1%26oauth_timestamp%3D1258019462%26oauth_version%3D1.0";
	const std::string key = "test_consumer_secret&";
	const std::string expect = "1aLqCNebhFXNj3o8Nyf5RIGsHEk=";

	const std::string signature = OAuthRequest::HmacSha1WithBase64Encode( source, key );

	EXPECT_EQ( expect, signature );
}

// HMAC-SHA1 + Base64 �֐��̃e�X�g
TEST( OAuthTest, HmacSha1Base64Func )
{
	const std::string source = "012345";
	const std::string key = "1";
	const std::string expect = "uSAq0a63u1W41eTdCrgbywm5CU8=";

	const std::string result = OAuthRequest::HmacSha1WithBase64Encode( source, key );

	EXPECT_EQ( expect, result );
}

// URL �G���R�[�f�B���O
TEST( OAuthTest, UrlEncoging )
{
	const std::string source = "https://auth.login.yahoo.co.jp/oauth/v2/get_request_token";
	const std::string expect = "https%3A%2F%2Fauth.login.yahoo.co.jp%2Foauth%2Fv2%2Fget_request_token";

	const std::string urlEnc = OAuthRequest::UrlEncode( source );

	EXPECT_EQ( expect, urlEnc );
}

// OpenSSL HMAC-SHA1 + Base64 �G���R�[�f�B���O
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

	// �ϊ�����������̍Ō�� CRLF �����Ă���̂ł�����Ƃ�B
	char b64withoutCRLF[256];
	int b64length = strlen( b64 );
	for( int i=0; i<b64length-2; i++ )	// CRLF ���� -2
	{
		b64withoutCRLF[i] = b64[i];
	}
	b64withoutCRLF[b64length-2] = 0;	// null ����
	
	// Python �ō�����l�Ɣ�r�B
	EXPECT_STREQ( "uSAq0a63u1W41eTdCrgbywm5CU8=", b64withoutCRLF );
}

// OpenSSL HMAC-SHA1 �̃e�X�g
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

	// �l�Ԃɕ����镶���ŕ\��
	for( int i=0; i<(int)sizeof( res ) - 1; i++ )
	{
		oss << boost::format( "%02x" ) % (int)res[i];
	}
	
	// Python �ō�����ꍇ�Ɣ�r
	EXPECT_STREQ( "b9202ad1aeb7bb55b8d5e4dd0ab81bcb09b9094f", oss.str().c_str() );
}