#include "stdafx.h"
#include "OAuthHandler.h"
#include "HttpClient.h"

// OAuth によるアクセスのテスト
TEST( OAuthConnectionTest, ApiByOAuth )
{
	std::ifstream ifs( "D:\\Documents\\Desktop\\cacoon_consumer_key.txt" );
	if( !ifs ) return;

	std::string consumer_key;
	ifs >> consumer_key;

	ifs.close();
	ifs.open( "D:\\Documents\\Desktop\\cacoon_consumer_secret.txt" );
	if( !ifs ) return;

	std::string consumer_secret;
	ifs >> consumer_secret;

	ifs.close();
	ifs.open( "D:\\Documents\\Desktop\\cacoon_access_key.txt" );
	if( !ifs ) return;

	std::string access_key;
	ifs >> access_key;

	ifs.close();
	ifs.open( "D:\\Documents\\Desktop\\cacoon_access_secret.txt" );
	if( !ifs ) return;

	std::string access_secret;
	ifs >> access_secret;

	OAuthHandler oauth( consumer_key, consumer_secret );
	oauth.SetAccessToken( access_key, access_secret );

	std::string authHeader = oauth.MakeAuthorizationHeader( "GET", "https://cacoo.com/api/v1/diagrams.xml" );

	Connection conn = HttpClient::CreateHttpsConnection( "cacoo.com" );
	Response resp = conn.Request( "GET", "/api/v1/diagrams.xml", HeaderMap( authHeader ) );

	EXPECT_EQ( 200, resp.StatusCode() );

	std::cout << resp.StatusCode() << std::endl;
	std::cout << resp.Header().ToString() << std::endl;
	std::cout << resp.Body();
}

//// アクセストークンの取得
//TEST( OAuthConnectionTest, GetAccessToken )
//{
//	std::ifstream ifs( "D:\\Documents\\Desktop\\cacoon_consumer_key.txt" );
//	if( !ifs ) return;
//
//	std::string consumer_key;
//	ifs >> consumer_key;
//
//	ifs.close();
//	ifs.open( "D:\\Documents\\Desktop\\cacoon_consumer_secret.txt" );
//	if( !ifs ) return;
//
//	std::string consumer_secret;
//	ifs >> consumer_secret;
//
//	OAuthHandler oauth( consumer_key, consumer_secret );
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