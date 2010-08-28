#include "stdafx.h"

#include "HttpClient.h"
#include "HeaderMap.h"

// ������̃��X�|���X�̃e�X�g
TEST( HttpConnectionTest, MultiRequest )
{
	EXPECT_NO_THROW(
	{
		try
		{
			Connection c = HttpClient::CreateHttpConnection( "cacoo.com" );
			Response res1st = c.Request( Method::Get, "/" );
			Response res2nd = c.Request( Method::Get, "/features" );
		}
		catch( const CacoonException & ex )
		{
			std::cout << ex.Info() << std::endl;
			throw;
		}
	} );
}

// ���ۂ� HTTP �ʐM�����Ă݂�
TEST( HttpConnectionTest, RealConnection )
{
	Connection c = HttpClient::CreateHttpConnection( "www.google.co.jp" );
	Response res = c.Request( Method::Get, "/index.html" );
	//std::cout << res.Header().ToString() << "\r\n" << res.Body() << std::endl;
	ASSERT_EQ( res.StatusCode(), 200 );
}