#include "stdafx.h"
#include "HeaderMap.h"

// Update のテスト
TEST( HeaderMapTest, HeaderMapUpdate )
{
	HeaderMap hm;
	hm["1"] = "one";
	hm["2"] = "two";

	HeaderMap hm2;
	hm2["1"] = "uno";
	hm2["3"] = "tre";

	hm.Update( hm2 );

	EXPECT_TRUE( hm.IsKeyExists( "3" ) );
	EXPECT_STREQ( "uno", hm["1"].c_str() );
}

// const イテレータのテスト
TEST( HeaderMapTest, HeaderMapConstIterator )
{
	HeaderMap hm;

	const std::string values[] = { "one", "two", "three" };

	hm["1"] = "one";
	hm["2"] = "two";
	hm["3"] = "three";

	const HeaderMap & chm = hm;
	int i = 0;
	for( HeaderMap::const_iterator it = chm.Begin(); it != chm.End(); it++ )
	{
		EXPECT_EQ( it->second, values[i++] );
	}
}

// イテレータのテスト
TEST( HeaderMapTest, HeaderMapIterator )
{
	HeaderMap hm;

	std::string values[] = { "one", "two", "three" };

	hm["1"] = "one";
	hm["2"] = "two";
	hm["3"] = "three";
	int i = 0;
	for( HeaderMap::iterator it = hm.Begin(); it != hm.End(); it++ )
	{
		EXPECT_EQ( it->second, values[i++] );
	}
}

// ヘッダマップの全削除
TEST( HeaderMapTest, HeaderMapClear )
{
	HeaderMap hm;

	hm.Insert( "Test", "clear test" );
	hm.Insert( "Test2", "are all items deleted" );

	hm.Clear();

	ASSERT_FALSE( hm.IsKeyExists( "Test" ) );
	ASSERT_FALSE( hm.IsKeyExists( "Test2" ) );
}

// ヘッダマップの削除
TEST( HeaderMapTest, HeaderMapDeletation )
{
	HeaderMap hm;

	hm.Insert( "Test", "deletation test" );

	ASSERT_TRUE( hm.IsKeyExists( "Test" ) );

	hm.Erase( "Test" );

	EXPECT_FALSE( hm.IsKeyExists( "Test" ) );
}

// ヘッダマップの挿入
TEST( HeaderMapTest, HeaderMapInsertion )
{
	HeaderMap hm;

	hm.Insert( "TestHeader1", "inserted by function" );
	hm["TestHeader2"] = "inserted by indexer";

	// キーが存在するか
	ASSERT_TRUE( hm.IsKeyExists( "TestHeader1" ) );	
	ASSERT_TRUE( hm.IsKeyExists( "TestHeader2" ) );

	// 挿入された値が正しいか
	EXPECT_EQ( hm["TestHeader1"], "inserted by function" );
	EXPECT_EQ( hm["TestHeader2"], "inserted by indexer" );
}

// ヘッダマップの文字列<->マップ相互変換テスト
TEST( HeaderMapTest, InteractiveConversion )
{
	std::string header = "TestHeader1: this is a test value\r\nTestHeader2: having two elements\r\n";

	HeaderMap hm( header );

	ASSERT_EQ( hm.ToString(), header );
}

// ヘッダマップの作成テスト
TEST( HeaderMapTest, HeaderMapCreation )
{
	std::string header = "TestHeader1: this is a test value\r\nTestHeader2: having two elements\r\n";
	
	HeaderMap hm( header );

	ASSERT_TRUE( hm.IsKeyExists( "TestHeader1" ) );
	ASSERT_FALSE( hm.IsKeyExists( "TestHeader3" ) );
}
