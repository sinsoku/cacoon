#include "stdafx.h"
#include "HttpClient.h"
#include "Connection.h"
#include "Response.h"
#include "HeaderMap.h"

// �w�b�_�}�b�v�̍폜
TEST( HeaderMapTest, HeaderMapDeletation )
{
	HeaderMap hm;

	hm.Insert( "Test", "deletation test" );

	ASSERT_TRUE( hm.IsKeyExists( "Test" ) );

	hm.Erase( "Test" );

	EXPECT_FALSE( hm.IsKeyExists( "Test" ) );
}

// �w�b�_�}�b�v�̑}��
TEST( HeaderMapTest, HeaderMapInsertion )
{
	HeaderMap hm;

	hm.Insert( "TestHeader1", "inserted by function" );
	hm["TestHeader2"] = "inserted by indexer";

	ASSERT_EQ( hm["TestHeader1"], "inserted by function" );
	ASSERT_EQ( hm["TestHeader2"], "inserted by indexer" );
}

// �w�b�_�}�b�v�̍쐬�e�X�g
TEST( HeaderMapTest, HeaderMapCreation )
{
	std::string header = "TestHeader1: this is a test value\r\nTestHeader2: having two elements\r\n";
	
	HeaderMap hm( header );

	ASSERT_TRUE( hm.IsKeyExists( "TestHeader1" ) );
	ASSERT_FALSE( hm.IsKeyExists( "TestHeader3" ) );
}


// �^�� HTTP �ʐM�e�X�g
TEST( HttpTest, CreateMockConnection )
{
	Connection conn = HttpClient::CreateMockConnection( "Mock" );
	Response resp = conn.Request( Method::Get, "/" );
	ASSERT_EQ( resp.StatusCode(), 200 );
}

// �\�P�b�g�쐬�e�X�g
TEST( SocketTest, CreateSocket )
{
	WSADATA wsaData;

	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );

	ASSERT_EQ( err, 0 );

	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );	// TCP �̃\�P�b�g���쐬

	EXPECT_NE( sock, INVALID_SOCKET );

	WSACleanup();
}

// WinSock2 �������e�X�g
TEST( SocketTest, InitializeWinSock )
{
	WSADATA wsaData;
	int err = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );
	
	ASSERT_EQ( err, 0 );

	WSACleanup();
}