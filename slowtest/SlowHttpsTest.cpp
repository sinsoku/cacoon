#include "stdafx.h"
#include "HttpClient.h"

// �ȈՐڑ��̃e�X�g
TEST( HttpsConnectionTest, EasyRequest )
{
	Response resp = HttpClient::Connect( Method::Get, "https://cohama.backlog.jp/LoginDisplay.action;jsessionid=E3E47A1EE360473E09AAB64426083937.h" );
	EXPECT_EQ( 200, resp.StatusCode() );
	std::cout << resp.Body();
}

// HTTPS �̕����񃊃N�G�X�g
TEST( HttpsConnectionTest, MultiRequest )
{
	EXPECT_NO_THROW(
	{
		try
		{
			const std::string host = "cohama.backlog.jp";
			const std::string url = "/LoginDisplay.action;jsessionid=E3E47A1EE360473E09AAB64426083937.h";

			Connection conn = HttpClient::CreateHttpsConnection( host );
			Response res1st = conn.Request( Method::Get, url );
			Response res2nd = conn.Request( Method::Get, url );

			conn = HttpClient::CreateHttpsConnection( host );

			Response res3rd = conn.Request( Method::Get, url );

			EXPECT_EQ( 200, res1st.StatusCode() );
			EXPECT_EQ( 200, res2nd.StatusCode() );
			EXPECT_EQ( 200, res3rd.StatusCode() );
		}
		catch( const CacoonException & ex )
		{
			std::cout << ex.Info() << std::endl;
			throw;
		}
	} );
}

// ���ۂ� HTTPS �ʐM�����Ă݂�
TEST( HttpsConnectionTest, RealConnection )
{
	const std::string host = "cohama.backlog.jp";
	const std::string url = "/LoginDisplay.action;jsessionid=E3E47A1EE360473E09AAB64426083937.h";

	Connection c = HttpClient::CreateHttpsConnection( host );
	Response res = c.Request( Method::Get, url );

	EXPECT_EQ( 200, res.StatusCode() );
						
	//std::cout << res.StatusCode() << std::endl;
	//std::cout << res.Header().ToString() << "\r\n" << res.Body() << std::endl;
}