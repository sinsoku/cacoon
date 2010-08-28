#include "stdafx.h"
#include "HttpConnection.h"

HttpConnection::HttpConnection( const std::string & hostname )
	: host( hostname )
{
	this->sock = ConnectionImpl::MakeSocket();
	this->addr = ConnectionImpl::MakeAddressFamily( this->sock, hostname, 80 );
	closesocket( this->sock );
}


HttpConnection::~HttpConnection()
{
}

Response HttpConnection::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	if( header.IsKeyExists( "Host" ) )
	{
		throw CACOON_EXCEPTION( "Host �w�b�_�͕K�v����܂���B" );
	}
	if( header.IsKeyExists( "Connection" ) )
	{
		throw CACOON_EXCEPTION( "Connection �w�b�_�͌����_�ł͑Ή����Ă��܂���B" );
	}
	std::ostringstream ossReq( std::ios::binary ); // \r\n �𐳂����������邽�߃o�C�i���Ƃ���B
	ossReq << method << " " << url << " HTTP/1.1\r\n"
		"Host: " << this->host << "\r\n"
		"Connection: close\r\n"
		<< header.ToString() << "\r\n" << '\0';

	// �R�l�N�V�����m��
	this->sock = ConnectionImpl::MakeSocket();
	ConnectionImpl::Connect( this->sock, this->addr );
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
	while( n > 0 )
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