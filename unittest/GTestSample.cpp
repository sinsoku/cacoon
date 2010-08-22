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

// TinyXml�̊m�F�p�̃e�X�g�P�[�X
TEST(GTestSample, TinyXmlTest) {
	std::string xmltmpfile = "xmldata.xml";
	char xmldata[] =
		"<?xml version=\"1.0\" ?>\n"
		"<Hello>World</Hello>\n";

	// �e���v�t�@�C���ɏ�����
	std::ofstream ofs(xmltmpfile);
	ofs << xmldata;
	ofs.close();

	// TinyXml�œǍ���
	TiXmlDocument doc(xmltmpfile.c_str());
	doc.LoadFile();

	TiXmlElement* root = doc.RootElement();
	EXPECT_STREQ("Hello", root->Value());
	EXPECT_STREQ("World", root->GetText());

	// �e���v�t�@�C���̍폜
	remove(xmltmpfile.c_str());
}