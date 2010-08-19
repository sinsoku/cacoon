#pragma once
#include "Response.h"

// Connection の内部実装のための抽象クラス
// Http と Https の違いを吸収するためのインターフェースとしてふるまう
class ConnectionImpl
{
public:
	virtual Response Request( const std::string & method, const std::string & url, const std::string & header ) = 0;
	virtual ~ConnectionImpl() {}
};
