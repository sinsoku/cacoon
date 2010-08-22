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

// TinyXmlの確認用のテストケース
TEST(GTestSample, TinyXmlTest) {
	std::string xmltmpfile = "xmldata.xml";
	char xmldata[] =
		"<?xml version=\"1.0\" ?>\n"
		"<Hello>World</Hello>\n";

	// テンプファイルに書込み
	std::ofstream ofs(xmltmpfile);
	ofs << xmldata;
	ofs.close();

	// TinyXmlで読込み
	TiXmlDocument doc(xmltmpfile.c_str());
	doc.LoadFile();

	TiXmlElement* root = doc.RootElement();
	EXPECT_STREQ("Hello", root->Value());
	EXPECT_STREQ("World", root->GetText());

	// テンプファイルの削除
	remove(xmltmpfile.c_str());
}