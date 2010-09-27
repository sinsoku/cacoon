#include "stdafx.h"
#include "OAuthHandler.h"
#include "HttpClient.h"

// リクエストトークンを試しに取得してみる
TEST( OAuthConnectionTest, GetRequestToken )
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

	OAuthHandler oauth( consumer_key, consumer_secret );
	oauth.SetOAuthUrl( "cacoo.com", "/oauth/", true );
	OAuthToken reqToken = oauth.GetRequestToken();

	std::cout << "key: " << reqToken.Key << std::endl << "sec: " << reqToken.Secret << std::endl;
}