#include "stdafx.h"

TEST( HttpsTest, OpenSslInitialization )
{
	SSL_load_error_strings();
	SSL_library_init();

	ASSERT_TRUE( true );
}