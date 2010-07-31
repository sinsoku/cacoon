#include <gtest/gtest.h>
#include <boost/foreach.hpp>

#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )

TEST(GTestSample, Assert) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	EXPECT_FALSE(false);
}

TEST(GTestSample, BoostTest) {
	int evenarray[] = {2,4,6,8,10};

	BOOST_FOREACH(int& x, evenarray) {
		EXPECT_TRUE(x % 2 == 0);
	}
}
