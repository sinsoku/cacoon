#include "stdafx.h"
#include "HttpClient.h"

// ���ۂ� HTTPS �ʐM�����Ă݂�
//TEST( HttpsConnectionTest, RealConnection )
//{
//	EXPECT_NO_THROW(
//	{
//		try
//		{
//			Connection c = HttpClient::CreateHttpsConnection( "cacoo.com" );
//			Response res = c.Request( Method::Get, "/oauth/access_token" );
//
//			std::cout << res.Header() << "\r\n" << res.Body() << std::endl;
//		}
//		catch( const CacoonException & ex )
//		{
//			std::cout << ex.Info() << std::endl;
//			throw;
//		}
//	} );
//}