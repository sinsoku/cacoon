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

void ConnectionImpl::MakeConnection( const char * host, int port )
{
}