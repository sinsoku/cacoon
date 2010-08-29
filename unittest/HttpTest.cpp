#include "stdafx.h"
#include "HttpClient.h"

#include "Connection.h"

#include "MockConnection.h"
#include "Response.h"

// 疑似 HTTP 通信テスト
TEST( HttpTest, CreateMockConnection )
{
	boost::shared_ptr<ConnectionImpl> pConn( new MockConnection( "Mock" ) );
	Response resp = pConn->Request( Method::Get, "/", HeaderMap() );
	EXPECT_EQ( 200, resp.StatusCode() );
}

// ソケット作成テスト
TEST( SocketTest, CreateSocket )
{
	WSADATA wsaData;

	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );

	ASSERT_EQ( err, 0 );

	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );	// TCP のソケットを作成

	EXPECT_NE( INVALID_SOCKET, sock );

	WSACleanup();
}

// WinSock2 初期化テスト
TEST( SocketTest, InitializeWinSock )
{
	WSADATA wsaData;
	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );
	
	EXPECT_EQ( 0, err );

	WSACleanup();
}