#include "stdafx.h"

#include "HttpClient.h"
#include "HeaderMap.h"

// 簡易接続のテスト
TEST( HttpConnectionTest, EasyRequest )
{
	Response resp = HttpClient::Connect( Method::Get, "http://cacoo.com/" );
	EXPECT_EQ( 200, resp.StatusCode() );
}

// 複数回のレスポンスのテスト
TEST( HttpConnectionTest, MultiRequest )
{
	EXPECT_NO_THROW(
	{
		try
		{
			Connection c = HttpClient::CreateHttpConnection( "cacoo.com" );
			Response res1st = c.Request( Method::Get, "/" );
			Response res2nd = c.Request( Method::Get, "/features" );

			EXPECT_EQ( 200, res1st.StatusCode() );
			EXPECT_EQ( 200, res2nd.StatusCode() );

			Connection c2 = c;
			Response res3rd = c2.Request( Method::Get, "/" );

			EXPECT_EQ( 200, res3rd.StatusCode() );
		}
		catch( const CacoonException & ex )
		{
			std::cout << ex.Info() << std::endl;
			throw;
		}
	} );
}

// 実際に HTTP 通信をしてみる
TEST( HttpConnectionTest, RealConnection )
{
	Connection c = HttpClient::CreateHttpConnection( "www.google.co.jp" );
	Response res = c.Request( Method::Get, "/index.html" );
	//std::cout << res.Header().ToString() << "\r\n" << res.Body() << std::endl;
	EXPECT_EQ( 200, res.StatusCode() );
}