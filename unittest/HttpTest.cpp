#include "stdafx.h"
#include "HttpClient.h"
#include "Connection.h"
#include "Response.h"

// 疑似 HTTP 通信テスト
TEST( HttpTest, CreateMockConnection )
{
	Connection conn = HttpClient::CreateMockConnection( "Mock" );
	Response resp = conn.Request( Method::Get, "/" );
	ASSERT_EQ( resp.StatusCode(), 200 );
}

// ソケット作成テスト
TEST( SocketTest, CreateSocket )
{
	WSADATA wsaData;

	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );

	ASSERT_EQ( err, 0 );

	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );	// TCP のソケットを作成

	EXPECT_NE( sock, INVALID_SOCKET );

	WSACleanup();
}

// WinSock2 初期化テスト
TEST( SocketTest, InitializeWinSock )
{
	WSADATA wsaData;
	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );
	
	ASSERT_EQ( err, 0 );

	WSACleanup();
}