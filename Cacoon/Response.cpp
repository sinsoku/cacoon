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

	if( headerOffset == std::string::npos )
	{
		throw CACOON_EXCEPTION( "サーバーからのレスポンスがありませんでした" );
	}

	this->header = rawResponse.substr( 0, headerOffset+2 );	// ヘッダとの区切りの CRLF を一つ含む。
	this->body = rawResponse.substr( headerOffset+4 );		// ヘッダとの区切りの CRLF は含まない。
}
// ヘッダ文字列→ std::map への変換
void Response::HeaderToMap( const std::string & header, HeaderMap * pMapOut )
{
	pMapOut->clear();	// 念のため要素を削除

	typedef boost::char_separator<char> Separator;	// 区切り文字クラス
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;	// 分割クラス

	Separator lineSep( "\r\n" );		// 1 行ごとに区切る
	Tokenizer line( header, lineSep );

	Separator elementSep( ":" );		// 1 行を : で区切る

	for( auto it = line.begin(); it != line.end(); it++ )
	{
		Tokenizer element( *it, elementSep );
		
		auto elemIt = element.begin();

		std::string key = *elemIt++;			// : より前
		std::string val = elemIt->substr( 1 );	// : より後

		(*pMapOut)[key] = val;	// map に登録
	}
}

// std::map → ヘッダ文字列への変換
void Response::MapToHeader( const HeaderMap & map, std::string * pHeaderOut )
{
	pHeaderOut->clear();	// 念のため削除

	std::ostringstream oss;

	for( auto it = map.begin(); it != map.end(); it++ )
	{
		oss << it->first << ": " << it->second << "\r\n";
	}

	//pHeaderOut
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