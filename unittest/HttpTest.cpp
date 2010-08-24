#include "stdafx.h"
#include "HttpClient.h"
#include "Connection.h"
#include "Response.h"
#include "HeaderMap.h"

// ヘッダマップの削除
TEST( HeaderMapTest, HeaderMapDeletation )
{
	HeaderMap hm;

	hm.Insert( "Test", "deletation test" );

	ASSERT_TRUE( hm.IsKeyExists( "Test" ) );

	hm.Erase( "Test" );

	EXPECT_FALSE( hm.IsKeyExists( "Test" ) );
}

// ヘッダマップの挿入
TEST( HeaderMapTest, HeaderMapInsertion )
{
	HeaderMap hm;

	hm.Insert( "TestHeader1", "inserted by function" );
	hm["TestHeader2"] = "inserted by indexer";

	ASSERT_EQ( hm["TestHeader1"], "inserted by function" );
	ASSERT_EQ( hm["TestHeader2"], "inserted by indexer" );
}

// ヘッダマップの作成テスト
TEST( HeaderMapTest, HeaderMapCreation )
{
	std::string header = "TestHeader1: this is a test value\r\nTestHeader2: having two elements\r\n";
	
	HeaderMap hm( header );

	ASSERT_TRUE( hm.IsKeyExists( "TestHeader1" ) );
	ASSERT_FALSE( hm.IsKeyExists( "TestHeader3" ) );
}


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