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
	static void MakeSocket( SOCKET * pSocketOut );

	// コネクションの確立
	static void MakeConnection( SOCKET sock, const std::string & host, int port );
};
