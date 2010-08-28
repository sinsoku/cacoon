#include "stdafx.h"
#include "HttpClient.h"

#include "Connection.h"

#include "MockConnection.h"
#include "Response.h"

// �^�� HTTP �ʐM�e�X�g
TEST( HttpTest, CreateMockConnection )
{
	boost::shared_ptr<ConnectionImpl> pConn( new MockConnection( "Mock" ) );
	Response resp = pConn->Request( Method::Get, "/", HeaderMap() );
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