#include "stdafx.h"
#include "HttpConnection.h"
#include "HeaderMap.h"

HttpConnection::HttpConnection( const std::string & hostname )
	: sock( hostname, 80 )
	, host( hostname )
{
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
	this->sock.Connect();
	// HTTP ���N�G�X�g���M
	int n = send( this->sock.Socket(), ossReq.str().c_str(), ossReq.str().length(), 0 );
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
		n = recv( this->sock.Socket(), buf, BufferSize, 0 );
		if( n < 0 )
		{
			throw CACOON_EXCEPTION( "recv �G���[" );
		}
		// ��M����
		ossResult.write( buf, n );
	}
	return Response( ossResult.str() );
}