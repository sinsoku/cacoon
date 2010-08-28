#pragma once
#include "Response.h"
class HeaderMap;
// Connection �̓��������̂��߂̒��ۃN���X
// Http �� Https �̈Ⴂ���z�����邽�߂̃C���^�[�t�F�[�X�Ƃ��Ăӂ�܂�
class ConnectionImpl
{
public:

	virtual Response Request( const std::string & method, const std::string & url, const HeaderMap & header ) = 0;
	virtual ~ConnectionImpl() {}

protected:

	// �\�P�b�g�̍쐬
	static SOCKET MakeSocket();

	// �A�h���X�t�@�~���[�̍쐬
	static SOCKADDR_IN MakeAddressFamily( SOCKET sock, const std::string & host, int port );

	// �ڑ��̊m��
	static void Connect( SOCKET sock, SOCKADDR_IN addr );
};
