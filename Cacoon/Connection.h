#pragma once
#include "stdafx.h"

#include "Method.h"
#include "Response.h"

class ConnectionImpl;

// host との接続を表すクラス
// 内部実装は ConnectionImpl の shared_ptr への委譲
class Connection
{
public:
	Response Request( const std::string & method, const std::string & url, const std::string & header = "" );

private:
	boost::shared_ptr<ConnectionImpl> pImpl;
	
	friend class HttpClient;	// HttpClient からのみ作成可能
	Connection( ConnectionImpl * pConnection );
};