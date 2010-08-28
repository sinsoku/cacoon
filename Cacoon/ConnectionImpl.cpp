#include "stdafx.h"
#include "ConnectionImpl.h"

// ソケットの作成
SOCKET ConnectionImpl::MakeSocket()
{
	SOCKET resultSocket = socket( AF_INET, SOCK_STREAM, 0 );

	if( resultSocket == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "ソケット初期化エラー" );
	}

	return resultSocket;
}

// アドレスファミリーの作成
SOCKADDR_IN ConnectionImpl::MakeAddressFamily( SOCKET sock, const std::string & hostname, int port )
{
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );
	server.sin_addr.S_un.S_addr = inet_addr( hostname.c_str() );
	if( server.sin_addr.S_un.S_addr == 0xFFFFFFFF )
	{	// host が文字列の場合
		hostent * host = gethostbyname( hostname.c_str() );
		if( host == NULL )
		{
			throw CACOON_EXCEPTION( "不明なホスト名" );
		}

		unsigned int ** addressList = (unsigned int **)host->h_addr_list;

		while( *addressList != NULL )
		{
			server.sin_addr.S_un.S_addr = **addressList;

			if( connect( sock, (sockaddr *)&server, sizeof( server ) ) == 0 )
			{	// connect が成功したらループを抜ける
				return server;
			}
			else
			{	// 次のアドレスをさす
				addressList++;
			}
		}
		// connect がすべて失敗した場合
		throw CACOON_EXCEPTION( "connect に失敗" );
	}
	else
	{	// host が数字列の場合
		if( connect( sock, (sockaddr *)&server, sizeof( server ) ) == 0 )
		{
			return server;
		}
		else
		{
			throw CACOON_EXCEPTION( "connect に失敗" );
		}
	}
}

// 接続の確立
void ConnectionImpl::Connect( SOCKET sock, SOCKADDR_IN addr  )
{
	int n = connect( sock, (sockaddr *)&addr, sizeof( addr ) );

	if( n != 0 )
	{
		throw CACOON_EXCEPTION( "connect に失敗" );
	}
}