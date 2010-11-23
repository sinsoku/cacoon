#include "stdafx.h"
#include "OAuthHandler.h"
#include "HttpClient.h"

// トークンが保存されているディレクトリ
const std::string TokenDirectory = "D:\\Documents\\Desktop\\";

// コンシューマトークンを取得
static bool LoadConsumerToken( std::string * consumerKey, std::string * consumerSecret )
{
	std::ifstream ifs( TokenDirectory + "cacoon_consumer_key.txt" );
	if( !ifs ) return false;

	ifs >> *consumerKey;

	ifs.close();
	ifs.open( TokenDirectory + "cacoon_consumer_secret.txt" );
	if( !ifs ) return false;

	ifs >> *consumerSecret;

	ifs.close();

	return true;
}
// アクセストークンを取得
static bool LoadAccessToken( std::string * accessKey, std::string * accessSecret )
{
	std::ifstream ifs( "D:\\Documents\\Desktop\\cacoon_access_key.txt" );
	if( !ifs ) return false;

	ifs >> *accessKey;

	ifs.close();
	ifs.open( "D:\\Documents\\Desktop\\cacoon_access_secret.txt" );
	if( !ifs ) return false;

	ifs >> *accessSecret;

	ifs.close();

	return true;
}

// OAuthHandler クラスによるアクセステスト
TEST( OAuthConnectionTest, ApiByOAuthHandler )
{
	std::string consumer_key;
	std::string consumer_secret;
	std::string access_key;
	std::string access_secret;

	if( !LoadConsumerToken( &consumer_key, &consumer_secret ) ) return;
	if( !LoadAccessToken( &access_key, &access_secret ) ) return;

	OAuthHandler handler( consumer_key, consumer_secret, access_key, access_secret );

	EXPECT_NO_THROW(
	{
		handler.get( "https://cacoo.com/api/v1/users/cohama.xml" );
		handler.get( "https://cacoo.com/api/v1/users/cohama.json" );
		handler.get( "https://cacoo.com/api/v1/diagrams.xml" );
	} );
}

// OAuth によるアクセスのテスト
TEST( OAuthConnectionTest, ApiByOAuth )
{
	std::string consumer_key;
	std::string consumer_secret;
	std::string access_key;
	std::string access_secret;

	if( !LoadConsumerToken( &consumer_key, &consumer_secret ) ) return;
	if( !LoadAccessToken( &access_key, &access_secret ) ) return;

	OAuthUrlMaker oauth( consumer_key, consumer_secret );
	oauth.SetAccessToken( access_key, access_secret );

	Connection conn = HttpClient::CreateHttpsConnection( "cacoo.com" );

	std::string authHeader = oauth.MakeAuthorizationHeader( "GET", "https://cacoo.com/api/v1/users/cohama.json" );
	Response resp = conn.Request( "GET", "/api/v1/users/cohama.json", HeaderMap( authHeader ) );

	EXPECT_EQ( 200, resp.StatusCode() );

	authHeader = oauth.MakeAuthorizationHeader( "GET", "https://cacoo.com/api/v1/diagrams.xml" );
	resp = conn.Request( "GET", "/api/v1/diagrams.xml", HeaderMap( authHeader ) );

	EXPECT_EQ( 200, resp.StatusCode() );

	authHeader = oauth.MakeAuthorizationHeader( "GET", "https://cacoo.com/api/v1/users/cohama.xml" );
	resp = conn.Request( "GET", "/api/v1/users/cohama.xml", HeaderMap( authHeader ) );

	EXPECT_EQ( 200, resp.StatusCode() );
}


// アクセストークンの取得
//TEST( OAuthConnectionTest, GetAccessToken )
//{
//	std::string consumer_key;
//	std::string consumer_secret;
//
//	if( !LoadConsumerToken( &consumer_key, &consumer_secret ) ) return;
//
//	OAuthUrlMaker oauth( consumer_key, consumer_secret );
//
//	// ブラウザを表示する。
//	std::string authUrl = oauth.GetAuthorizationUrl();
//	ShellExecuteA( NULL, "open", authUrl.c_str(), NULL, NULL, SW_SHOWNORMAL );
//	
//	std::string verifier;
//	std::cout << "verifier: ";
//	std::cin >> verifier;
//	
//	OAuthToken accessToken = oauth.GetAccessToken( verifier );
//
//	ASSERT_STRNE( "", accessToken.Key.c_str() );
//	ASSERT_STRNE( "", accessToken.Secret.c_str() );
//
//	std::ofstream ofs( "D:\\Documents\\Desktop\\cacoon_access_key.txt" );
//	ofs << accessToken.Key;
//
//	ofs.close();
//	ofs.open( "D:\\Documents\\Desktop\\cacoon_access_secret.txt" );
//
//	ofs << accessToken.Secret;
//}