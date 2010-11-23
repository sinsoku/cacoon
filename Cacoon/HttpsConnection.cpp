#include "StdAfx.h"
#include "HttpsConnection.h"
#include "HeaderMap.h"

HttpsConnection::HttpsConnection( const std::string & host )
	: ConnectionImpl( host )
	, sock( host, 443 )
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

void HttpsConnection::makeConnection()
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

void HttpsConnection::sendRequest( const std::string & request )
{
	int n = SSL_write( this->ssl, request.c_str(), request.length() );
	if( n < 0 )
	{
		throw CACOON_EXCEPTION( "���N�G�X�g�̑��M�Ɏ��s" );
	}
}

int HttpsConnection::receive( char * buf, int bufferSize )
{
	memset( buf, 0, bufferSize );
	return SSL_read( this->ssl, buf, bufferSize );
}