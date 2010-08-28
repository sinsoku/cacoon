#include "stdafx.h"
#include "ConnectionImpl.h"

void ConnectionImpl::MakeSocket( SOCKET * pSocketOut )
{
	*pSocketOut = socket( AF_INET, SOCK_STREAM, 0 );

	if( *pSocketOut == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "ソケット初期化エラー" );
	}
}

void ConnectionImpl::MakeConnection( SOCKET sock, const std::string & hostname, int port )
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
				break;
			}
			else
			{	// 次のアドレスをさす
				addressList++;
			}
		}
		if( *addressList == NULL )
		{	// connect がすべて失敗した場合
			throw CACOON_EXCEPTION( "connect に失敗" );
		}
	}
	else
	{	// host が数字列の場合
		if( connect( sock, (sockaddr *)&server, sizeof( server ) ) != 0 )
		{
			throw CACOON_EXCEPTION( "connect に失敗" );
		}
	}
}