#include "stdafx.h"

// GoogleTest確認用のテストケース
TEST(GTestSample, GTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	EXPECT_FALSE(false);
}

// boostの確認用のテストケース
TEST(GTestSample, BoostTest) {
	int evenarray[] = {2,4,6,8,10};

	BOOST_FOREACH(int& x, evenarray) {
		EXPECT_TRUE(x % 2 == 0);
	}
}
