#include "stdafx.h"
#include "HttpConnection.h"

HttpConnection::HttpConnection( const std::string & hostname )
	: host( hostname )
{
	this->sock = socket( AF_INET, SOCK_STREAM, 0 );

	if( sock == INVALID_SOCKET )
	{
		throw CACOON_EXCEPTION( "�\�P�b�g�������G���[" );
	}

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


HttpConnection::~HttpConnection()
{
	closesocket( this->sock );
}

Response HttpConnection::Request( const std::string & method, const std::string & url, const std::string & header )
{
	std::ostringstream ossReq( std::ios::binary );
	ossReq << method << " " << url << " HTTP/1.1\r\nHost: " << this->host << "\r\n\r\n" << '\0';

	// HTTP ���N�G�X�g���M
	int n = send( this->sock, ossReq.str().c_str(), ossReq.str().length(), 0 );
	if( n < 0 )
	{
		throw CACOON_EXCEPTION( "send �G���[" );
	}

	std::ostringstream ossResult( std::ios::binary );

	const int BufferSize = 256;
	char buf[BufferSize];

	// �T�[�o����� HTTP ���b�Z�[�W��M
	while( n == BufferSize	 )
	{
		memset( buf, 0, BufferSize );
		n = recv( this->sock, buf, BufferSize, 0 );
		if( n < 0 )
		{
			throw CACOON_EXCEPTION( "recv �G���[" );
		}
		// ��M����
		ossResult.write( buf, BufferSize );
	}
	return Response( ossResult.str() );
}