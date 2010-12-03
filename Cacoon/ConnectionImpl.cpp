#include "stdafx.h"
#include "HeaderMap.h"
#include "ConnectionImpl.h"

ConnectionImpl::ConnectionImpl( const std::string & host )
	: HostName( host )
{
}

Response ConnectionImpl::Request( const std::string & method, const std::string & url, const HeaderMap & header )
{
	HeaderMap hm;
	hm["Host"] = this->HostName;
	hm["Connection"] = "close";
	hm.Update( header );

	std::ostringstream ossReq( std::ios::binary ); // \r\n �𐳂����������邽�߃o�C�i���Ƃ���B
	ossReq << method << " " << url << " HTTP/1.1\r\n" << hm.ToString() << "\r\n" << '\0';

	this->makeConnection();
	this->sendRequest( ossReq.str() );

	std::ostringstream ossResult( std::ios::binary );

	const int BufferSize = 256;
	char buf[BufferSize+1];

	// �T�[�o����w�b�_������M
	while( 1 )
	{
		int readSize = this->receive( buf, BufferSize );
		if( readSize > 0 )
		{
			buf[readSize] = '\0';
			std::string bufStr( buf );
			std::string::size_type endOfHeader = bufStr.find( "\r\n\r\n" );
			if( endOfHeader == std::string::npos )
			{
				ossResult.write( buf, readSize );
			}
			else
			{
				ossResult.write( buf, readSize );
				break;
			}
		}
		else if( readSize == 0 )
		{
			break;
		}
		else
		{
			throw CACOON_EXCEPTION( "recv �G���[" );
		}
	}
	std::string respHeaderStr = ossResult.str();
	std::string::size_type firstLine = respHeaderStr.find( "\r\n" );
	std::string::size_type lastLine = respHeaderStr.find( "\r\n\r\n" );
	HeaderMap respHeader( respHeaderStr.substr( firstLine + 2, lastLine - firstLine - 2 ) );

	if( respHeader["Transfer-Encoding"] == "chunked" )
	{	// �T�[�o���瑱������M (chunked �o�[�W����)
		int chunkSize = 0;
		while( 1 )
		{
			int readSize = this->receive( buf, BufferSize );
			if( chunkSize == 0 )
			{
				if( readSize == 0 )
				{
					break;
				}
				buf[readSize-2] = '\0';
				chunkSize = strtol( buf, NULL, 16 );
			}
			else
			{
				if( readSize > 0 )
				{
					ossResult.write( buf, readSize );
					chunkSize -= readSize;
				}
				else if( readSize == 0 )
				{
					break;
				}
				else
				{
					throw CACOON_EXCEPTION( "recv �G���[" );
				}
			}
		}
	}
	else
	{	// �T�[�o���瑱������M (����)
		while( 1 )
		{
			int readSize = this->receive( buf, BufferSize );
			if( readSize > 0 )
			{
				ossResult.write( buf, readSize );
				break;
			}
			else if( readSize == 0 )
			{
				break;
			}
			else
			{
				throw CACOON_EXCEPTION( "recv �G���[" );
			}
		}
	}
	return Response( ossResult.str() );
}