#include "StdAfx.h"
#include "SocketConnector.h"


SocketConnector::SocketConnector( const std::string & hostname, int port )
{
	this->makeSocket();	// �A�h���X�����̂��߈ꎞ�I�Ƀ\�P�b�g�쐬
	this->makeAddressFamily( hostname, port );
	closesocket( this->sock );
}

SocketConnector::~SocketConnector()
{
	closesocket( this->sock );
}

// �ڑ��̊J�n
void SocketConnector::Connect()
{
	this->makeSocket();
	int err = connect( sock, (sockaddr *)&this->addr, sizeof( this->addr ) );

	if( err != 0 )
	{
		throw CACOON_EXCEPTION( "connect �Ɏ��s" );
	}
}

// �\�P�b�g�̃Q�b�^�[
SOCKET SocketConnector::Socket()
{
	return this->sock;
}

// �\�P�b�g�̍쐬
void SocketConnector::makeSocket()
{
	this->sock = socket( AF_INET, SOCK_STREAM, 0 );

	if( this->sock == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "�\�P�b�g�������G���[" );
	}
}

// �A�h���X����
void SocketConnector::makeAddressFamily( const std::string & hostname, int port )
{
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons( port );
	this->addr.sin_addr.S_un.S_addr = inet_addr( hostname.c_str() );

	if( this->addr.sin_addr.S_un.S_addr == 0xFFFFFFFF )
	{	// host ��������̏ꍇ
		hostent * host = gethostbyname( hostname.c_str() );
		if( host == NULL )
		{
			throw CACOON_EXCEPTION( "�s���ȃz�X�g��" );
		}

		unsigned int ** addressList = (unsigned int **)host->h_addr_list;

		while( *addressList != NULL )
		{
			this->addr.sin_addr.S_un.S_addr = **addressList;

			if( connect( sock, (sockaddr *)&this->addr, sizeof( this->addr ) ) == 0 )
			{	// connect �����������烋�[�v�𔲂���
				break;
			}
			else
			{	// ���̃A�h���X������
				addressList++;
			}
		}
		if( *addressList == NULL )
		{	// connect �����ׂĎ��s�����ꍇ
			throw CACOON_EXCEPTION( "connect �Ɏ��s" );
		}
	}
	else
	{	// host ��������̏ꍇ
		if( connect( sock, (sockaddr *)&this->addr, sizeof( this->addr ) ) != 0 )
		{
			throw CACOON_EXCEPTION( "connect �Ɏ��s" );
		}
	}
}