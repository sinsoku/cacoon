#include "stdafx.h"
#include "Exceptions.h"

TEST( ExceptionText, ThrowingTest )
{
	bool thrown = false;
	try {
		throw CacoonException( "test", __FILE__, __LINE__ );
	} catch( const CacoonException & ) {
		thrown = true;
	}
	ASSERT_TRUE( thrown );
}

TEST( ExceptionTest, MacroThrowingTest )
{
	bool thrown = false;
	try
	{
		throw CACOON_EXCEPTION( "test" );
	}
	catch( const CacoonException & )
	{
		thrown = true;
	}
	ASSERT_TRUE( thrown );
}

TEST( ExceptionTest, ExceptionInfoTest )
{
	std::string file;
	int line;
	try
	{
		file = std::string( __FILE__ ); line = __LINE__; throw CACOON_EXCEPTION( "test" );
	}
	catch( const CacoonException & ex )
	{
		int messagePos = ex.Info().find( "test" );
		int filePos = ex.Info().find( file );
		int linePos = ex.Info().find( boost::lexical_cast<std::string>( line ) );

		EXPECT_EQ( messagePos, 0 );
		EXPECT_NE( filePos, std::string::npos );
		EXPECT_NE( linePos, std::string::npos );
	}
}