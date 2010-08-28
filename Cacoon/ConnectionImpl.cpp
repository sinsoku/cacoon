#include "stdafx.h"
#include "ConnectionImpl.h"

void ConnectionImpl::MakeSocket( SOCKET * pSocketOut )
{
	*pSocketOut = socket( AF_INET, SOCK_STREAM, 0 );

	if( *pSocketOut == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "�\�P�b�g�������G���[" );
	}
}

void ConnectionImpl::MakeConnection( SOCKET sock, const std::string & hostname, int port )
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
		if( connect( sock, (sockaddr *)&server, sizeof( server ) ) != 0 )
		{
			throw CACOON_EXCEPTION( "connect �Ɏ��s" );
		}
	}
}