#pragma once
#include "stdafx.h"

#include "Method.h"
#include "Response.h"

class ConnectionImpl;

// host �Ƃ̐ڑ���\���N���X
// ���������� ConnectionImpl �� shared_ptr �ւ̈Ϗ�
class Connection
{
public:
	Response Request( const std::string & method, const std::string & url, const std::string & header = "" );

private:
	boost::shared_ptr<ConnectionImpl> pImpl;
	
	friend class HttpClient;	// HttpClient ����̂ݍ쐬�\
	Connection( ConnectionImpl * pConnection );
};