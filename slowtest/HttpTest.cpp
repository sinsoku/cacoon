#include "stdafx.h"

#include "HttpClient.h"
#include "HeaderMap.h"

// 複数回のレスポンスのテスト
TEST( HttpConnectionTest, MultiRequest )
{
	EXPECT_NO_THROW(
	{
		Connection c = HttpClient::CreateHttpConnection( "cacoo.com" );
		Response res1st = c.Request( Method::Get, "/" );
		Response res2nd = c.Request( Method::Get, "/features" );
	} );
}

// 実際に HTTP 通信をしてみる
TEST( HttpConnectionTest, RealConnection )
{
	Connection c = HttpClient::CreateHttpConnection( "www.google.co.jp" );
	Response res = c.Request( Method::Get, "/index.html" );
	ASSERT_EQ( res.StatusCode(), 200 );
}