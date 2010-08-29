#pragma once

// �\�P�b�g�R�l�N�V�������m�����邽�߂̃N���X
// SOCKET �� SOCKADDR_IN �\���̂����b�s���O���܂��B
class SocketConnector
{
public:
	SocketConnector( const std::string & hostname, int port );
	~SocketConnector();

	// �ڑ��̊J�n�B���N�G�X�g�𑗂�O�ɌĂ΂��B
	void Connect();

	// �\�P�b�g�̃Q�b�^�[
	SOCKET Socket();

private:
	SOCKET sock;
	SOCKADDR_IN addr;

	void makeSocket();
	void makeAddressFamily( const std::string & hostname, int port );
};

