#include "StdAfx.h"
#include "HttpsConnection.h"
#include "HeaderMap.h"

HttpsConnection::HttpsConnection( const std::string & host )
	: sock( host, 443 )
	, host( host )
{
	SSL_load_error_strings();
	SSL_library_init();

	// �g�p����v���g�R���̌���
	this->ctx = SSL_CTX_new( SSLv23_client_method() );
	if( ctx == NULL )
	{
		ERR_print_errors_fp( stderr );
		throw CACOON_EXCEPTION( "�v���g�R��������ł��܂���ł����B" );
	}

	// �R�l�N�V�������Ǘ����� SSL �\���̂̍쐬
	this->ssl = SSL_new( ctx );
	if( ssl == NULL )
	{
		ERR_print_errors_fp( stderr );
		throw CACOON_EXCEPTION( "SSL �̏������Ɏ��s���܂����B" );
	}

	// �����̎�̐ݒ�
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
			throw CACOON_EXCEPTION( "SSL �̏I���Ɏ��s" );
		}
	}
	SSL_free( this->ssl );
	SSL_CTX_free( this->ctx );
	ERR_free_strings();
}

Response HttpsConnection::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	HeaderMap hm( header );
	if( !hm.IsKeyExists( "Host" ) )
	{
		hm.Insert( "Host", this->host );
	}
	if( !hm.IsKeyExists( "Connection" ) )
	{
		hm.Insert( "Connection", "close" );
	}
	std::ostringstream ossReq( std::ios::binary ); // \r\n �𐳂����������邽�߃o�C�i���Ƃ���B
	ossReq << method << " " << url << " HTTP/1.1\r\n" << hm.ToString() << "\r\n" << '\0';

	this->makeSslConnection();

	int n = SSL_write( this->ssl, ossReq.str().c_str(), ossReq.str().length() );

	std::ostringstream ossResult( std::ios::binary );
	
	const int BufferSize = 256;
	char buf[BufferSize];

	// �T�[�o�[����̎�M
	while( 1 )
	{
		int readSize = SSL_read( ssl, buf, BufferSize );
		if( readSize > 0 )
		{
			ossResult.write( buf, readSize );
		}
		else if( readSize == 0 )
		{
			break;
		}
		else
		{
			ERR_print_errors_fp( stderr );
			throw CACOON_EXCEPTION( "��M�Ɏ��s" );
		}
	}
	return Response( ossResult.str() );
}

void HttpsConnection::makeSslConnection()
{
	// �\�P�b�g�̐ڑ�
	this->sock.Connect();

	// �\�P�b�g�� SSL ������
	int n = SSL_set_fd( this->ssl, this->sock.Socket() );
	if( n == 0 )
	{
		ERR_print_errors_fp( stderr );
		throw CACOON_EXCEPTION( "�\�P�b�g�� SSL �����ׂ܂���ł����B" );
	}

	// SSL �R�l�N�V�����̊m��
	n = SSL_connect( this->ssl );
	if( n != 1 )
	{
		ERR_print_errors_fp( stdout );
		throw CACOON_EXCEPTION( "connect �Ɏ��s" );
	}
}