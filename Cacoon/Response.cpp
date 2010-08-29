#include "stdafx.h"
#include "Response.h"
#include "HeaderMap.h"
// コンストラクタ
Response::Response( const std::string & rawResponse )
{
	if( rawResponse.length() < 13 )
	{
		throw CACOON_EXCEPTION( "レスポンス文字列が不正です" );
	}
	const int StatusOffset = 9;	// ステータスコードはレスポンスヘッダの 9 文字目から始まる。
	char statusCodeAsString[4];

	for( int i=0; i<3; i++ )
	{
		statusCodeAsString[i] = rawResponse[i+StatusOffset];
	}
	statusCodeAsString[3] = '\0';

	this->statusCode = boost::lexical_cast<int, char *>( statusCodeAsString );

	int endOfFirstLine = rawResponse.find( "\r\n" );	// 最初のレスポンス行は無視する。
	int headerOffset = rawResponse.find( "\r\n\r\n" );	// ヘッダは最初の CR LF CR LF まで

	if( endOfFirstLine == std::string::npos || headerOffset == std::string::npos )
	{
		throw CACOON_EXCEPTION( "サーバーからのレスポンスがありませんでした" );
	}
	// レスポンス行の CRLF を含まず、ヘッダとの区切りの CRLF を一つ含む。
	this->header = boost::shared_ptr<HeaderMap>( new HeaderMap( rawResponse.substr( endOfFirstLine+2, headerOffset-endOfFirstLine ) ) );
	// ヘッダとの区切りの CRLF は含まない。
	this->body = rawResponse.substr( headerOffset+4 );
}


// ゲッター
int Response::StatusCode()
{
	return this->statusCode;
}

const HeaderMap & Response::Header()
{
	return *this->header;
}

const std::string & Response::Body()
{
	return this->body;
}