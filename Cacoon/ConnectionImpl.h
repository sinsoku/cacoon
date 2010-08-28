#pragma once
#include "Response.h"
class HeaderMap;
// Connection の内部実装のための抽象クラス
// Http と Https の違いを吸収するためのインターフェースとしてふるまう
class ConnectionImpl
{
public:

	virtual Response Request( const std::string & method, const std::string & url, const HeaderMap & header ) = 0;
	virtual ~ConnectionImpl() {}

protected:

	// ソケットの作成
	static SOCKET MakeSocket();

	// アドレスファミリーの作成
	static SOCKADDR_IN MakeAddressFamily( SOCKET sock, const std::string & host, int port );

	// 接続の確立
	static void Connect( SOCKET sock, SOCKADDR_IN addr );
};
