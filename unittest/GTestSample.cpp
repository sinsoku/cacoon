#include "stdafx.h"

// GoogleTest�m�F�p�̃e�X�g�P�[�X
TEST(GTestSample, GTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	EXPECT_FALSE(false);
}

// boost�̊m�F�p�̃e�X�g�P�[�X
TEST(GTestSample, BoostTest) {
	int evenarray[] = {2,4,6,8,10};

	BOOST_FOREACH(int& x, evenarray) {
		EXPECT_TRUE(x % 2 == 0);
	}
}
