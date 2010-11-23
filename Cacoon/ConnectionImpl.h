#pragma once
#include "Response.h"
#include "SocketConnector.h"

class HeaderMap;
// Connection �̓��������̂��߂̒��ۃN���X
// Http �� Https �̈Ⴂ���z�����邽�߂̃C���^�[�t�F�[�X�Ƃ��Ăӂ�܂�
class ConnectionImpl
{
public:

	explicit ConnectionImpl( const std::string & host );
	
	virtual Response Request( const std::string & method, const std::string & url, const HeaderMap & header );

protected:

	const std::string HostName;

private:

	virtual void makeConnection() = 0;
	virtual void sendRequest( const std::string & request ) = 0;
	virtual int receive( char * buf, int bufferSize ) = 0;

	// �R�s�[�֎~
	ConnectionImpl( const ConnectionImpl & );
	ConnectionImpl & operator = ( const ConnectionImpl & );

};
