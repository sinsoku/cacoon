#include "stdafx.h"
#include "ConnectionImpl.h"

// �\�P�b�g�̍쐬
SOCKET ConnectionImpl::MakeSocket()
{
	SOCKET resultSocket = socket( AF_INET, SOCK_STREAM, 0 );

	if( resultSocket == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "�\�P�b�g�������G���[" );
	}

	return resultSocket;
}

// �A�h���X�t�@�~���[�̍쐬
SOCKADDR_IN ConnectionImpl::MakeAddressFamily( SOCKET sock, const std::string & hostname, int port )
{
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );
	server.sin_addr.S_un.S_addr = inet_addr( hostname.c_str() );
	if( server.sin_addr.S_un.S_addr == 0xFFFFFFFF )
	{	// host ��������̏ꍇ
		hostent * host = gethostbyname( hostname.c_str() );
		if( host == NULL )
		{
			throw CACOON_EXCEPTION( "�s���ȃz�X�g��" );
		}

		unsigned int ** addressList = (unsigned int **)host->h_addr_list;

		while( *addressList != NULL )
		{
			server.sin_addr.S_un.S_addr = **addressList;

			if( connect( sock, (sockaddr *)&server, sizeof( server ) ) == 0 )
			{	// connect �����������烋�[�v�𔲂���
				return server;
			}
			else
			{	// ���̃A�h���X������
				addressList++;
			}
		}
		// connect �����ׂĎ��s�����ꍇ
		throw CACOON_EXCEPTION( "connect �Ɏ��s" );
	}
	else
	{	// host ��������̏ꍇ
		if( connect( sock, (sockaddr *)&server, sizeof( server ) ) == 0 )
		{
			return server;
		}
		else
		{
			throw CACOON_EXCEPTION( "connect �Ɏ��s" );
		}
	}
}

// �ڑ��̊m��
void ConnectionImpl::Connect( SOCKET sock, SOCKADDR_IN addr  )
{
	int n = connect( sock, (sockaddr *)&addr, sizeof( addr ) );

	if( n != 0 )
	{
		throw CACOON_EXCEPTION( "connect �Ɏ��s" );
	}
}