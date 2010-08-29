#include "StdAfx.h"
#include "SocketConnector.h"


SocketConnector::SocketConnector( const std::string & hostname, int port )
{
	this->makeSocket();	// アドレス解決のため一時的にソケット作成
	this->makeAddressFamily( hostname, port );
	closesocket( this->sock );
}

SocketConnector::~SocketConnector()
{
	closesocket( this->sock );
}

// 接続の開始
void SocketConnector::Connect()
{
	this->makeSocket();
	int err = connect( sock, (sockaddr *)&this->addr, sizeof( this->addr ) );

	if( err != 0 )
	{
		throw CACOON_EXCEPTION( "connect に失敗" );
	}
}

// ソケットのゲッター
SOCKET SocketConnector::Socket()
{
	return this->sock;
}

// ソケットの作成
void SocketConnector::makeSocket()
{
	this->sock = socket( AF_INET, SOCK_STREAM, 0 );

	if( this->sock == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "ソケット初期化エラー" );
	}
}

// アドレス解決
void SocketConnector::makeAddressFamily( const std::string & hostname, int port )
{
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons( port );
	this->addr.sin_addr.S_un.S_addr = inet_addr( hostname.c_str() );

	if( this->addr.sin_addr.S_un.S_addr == 0xFFFFFFFF )
	{	// host が文字列の場合
		hostent * host = gethostbyname( hostname.c_str() );
		if( host == NULL )
		{
			throw CACOON_EXCEPTION( "不明なホスト名" );
		}

		unsigned int ** addressList = (unsigned int **)host->h_addr_list;

		while( *addressList != NULL )
		{
			this->addr.sin_addr.S_un.S_addr = **addressList;

			if( connect( sock, (sockaddr *)&this->addr, sizeof( this->addr ) ) == 0 )
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
		if( connect( sock, (sockaddr *)&this->addr, sizeof( this->addr ) ) != 0 )
		{
			throw CACOON_EXCEPTION( "connect に失敗" );
		}
	}
}