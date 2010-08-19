#include "stdafx.h"
#include "Response.h"

// コンストラクタ
Response::Response( const std::string & rawResponse )
{
	const int StatusOffset = 9;	// ステータスコードはレスポンスヘッダの 9 文字目から始まる。
	char statusCodeAsString[4];

	for( int i=0; i<3; i++ )
	{
		statusCodeAsString[i] = rawResponse[i+StatusOffset];
	}
	statusCodeAsString[3] = '\0';

	this->statusCode = atoi( statusCodeAsString );

	int headerOffset = rawResponse.find( "\r\n\r\n" );	// ヘッダは最初の CR LF CR LF まで

	this->header = rawResponse.substr( 0, headerOffset+2 );	// ヘッダとの区切りの CRLF を一つ含む。
	this->body = rawResponse.substr( headerOffset+4 );		// ヘッダとの区切りの CRLF は含まない。

}


// ゲッター
int Response::StatusCode()
{
	return this->statusCode;
}

const std::string & Response::Header()
{
	return this->header;
}

const std::string & Response::Body()
{
	return this->body;
}