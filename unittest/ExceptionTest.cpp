#include <gtest/gtest.h>
#include "Exceptions.h"

#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )

TEST( ExceptionText, ThrowingTest )
{
	bool thrown = false;
	try {
		throw CacoonExceptionBase();
	} catch( CacoonExceptionBase & ) {
		thrown = true;
	}
	ASSERT_TRUE( thrown );
}