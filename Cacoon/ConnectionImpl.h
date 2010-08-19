#pragma once
#include "Response.h"

// Connection �̓��������̂��߂̒��ۃN���X
// Http �� Https �̈Ⴂ���z�����邽�߂̃C���^�[�t�F�[�X�Ƃ��Ăӂ�܂�
class ConnectionImpl
{
public:
	virtual Response Request( const std::string & method, const std::string & url, const std::string & header ) = 0;
	virtual ~ConnectionImpl() {}
};
