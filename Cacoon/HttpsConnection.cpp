#include "StdAfx.h"
#include "HttpsConnection.h"
#include "HeaderMap.h"

HttpsConnection::HttpsConnection( const std::string & host )
	: ConnectionImpl( host )
	, sock( host, 443 )
{
	SSL_load_error_strings();
	SSL_library_init();

	// 使用するプロトコルの決定
	this->ctx = SSL_CTX_new( SSLv23_client_method() );
	if( ctx == NULL )
	{
		ERR_print_errors_fp( stderr );
		throw CACOON_EXCEPTION( "プロトコルを決定できませんでした。" );
	}

	// コネクションを管理する SSL 構造体の作成
	this->ssl = SSL_new( ctx );
	if( ssl == NULL )
	{
		ERR_print_errors_fp( stderr );
		throw CACOON_EXCEPTION( "SSL の初期化に失敗しました。" );
	}

	// 乱数の種の設定
	while( RAND_status() == 0 )
	{
		unsigned short rand_ret = rand() % 65536;
		RAND_seed( &rand_ret, sizeof( rand_ret ) );
	}
}

HttpsConnection::~HttpsConnection()
{
	if( this->ssl->shutdown == SSL_RECEIVED_SHUTDOWN )
	{
		int n = SSL_shutdown( this->ssl );
		if( n != 1 )
		{
			ERR_print_errors_fp( stderr );
			throw CACOON_EXCEPTION( "SSL の終了に失敗" );
		}
	}
	SSL_free( this->ssl );
	SSL_CTX_free( this->ctx );
	ERR_free_strings();
}

void HttpsConnection::makeConnection()
{
	// ソケットの接続
	this->sock.Connect();

	// ソケットと SSL を結ぶ
	int n = SSL_set_fd( this->ssl, this->sock.Socket() );
	if( n == 0 )
	{
		ERR_print_errors_fp( stderr );
		throw CACOON_EXCEPTION( "ソケットと SSL を結べませんでした。" );
	}

	// SSL コネクションの確立
	n = SSL_connect( this->ssl );
	if( n != 1 )
	{
		ERR_print_errors_fp( stdout );
		throw CACOON_EXCEPTION( "connect に失敗" );
	}
}

void HttpsConnection::sendRequest( const std::string & request )
{
	int n = SSL_write( this->ssl, request.c_str(), request.length() );
	if( n < 0 )
	{
		throw CACOON_EXCEPTION( "リクエストの送信に失敗" );
	}
}

int HttpsConnection::receive( char * buf, int bufferSize )
{
	memset( buf, 0, bufferSize );
	return SSL_read( this->ssl, buf, bufferSize );
}