#pragma once
#include "OAuthConsumer.h"
class OAuthRequest
{
public:
	static OAuthRequest FromConsumerAndToken( const OAuthConsumer & consumer );

private:
	OAuthRequest();
	OAuthRequest( const OAuthRequest & );
	OAuthRequest & operator = ( const OAuthRequest & );
};

