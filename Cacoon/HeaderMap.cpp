#include "StdAfx.h"
#include "HeaderMap.h"

// コンストラクタ: 空のマップを作成
HeaderMap::HeaderMap()
{
}

// コンストラクタ: 文字列からマップを作成
HeaderMap::HeaderMap( const std::string & headerString )
{
	typedef boost::char_separator<char> Separator;	// 区切り文字クラス
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;	// 分割クラス

	Separator lineSep( "\r\n" );		// 1 行ごとに区切る
	Tokenizer line( headerString, lineSep );

	Separator elementSep( ":" );		// 1 行を : で区切る
	Tokenizer::iterator it = line.begin();
	it++;	// 1 行目は読み飛ばす。(レスポンスヘッダは 2 行目から始まる)
	for( ; it != line.end(); it++ )
	{
		Tokenizer element( *it, elementSep ); // : で区切る
		
		Tokenizer::iterator elemIt = element.begin();

		std::string key = *elemIt++;			// Key は : より前
		int spaceCount = 0;	// : 以降の文字列で先頭にあるスペースの数を数える
		for( std::string::const_iterator it = elemIt->begin(); it != elemIt->end(); it++ )
		{
			if( *it == ' ' )
			{
				spaceCount++;
			}
			else
			{
				break;
			}
		}
		// Value は : より後の先頭のスペースを削除したもの (文字数が 0 のときやスペースしかないときは空文字とする)
		std::string value = (spaceCount != elemIt->length()) ? elemIt->substr( spaceCount ) : "" ;

		this->innerMap.insert( std::map<std::string, std::string>::value_type( key, value ) );	// map に登録
	}
}

// マップから文字列を作成
std::string HeaderMap::ToString() const
{
	std::ostringstream oss;

	for( std::map<std::string, std::string>::const_iterator it = this->innerMap.begin(); it != this->innerMap.end(); it++ )
	{
		oss << it->first << ": " << it->second << "\r\n";
	}

	return oss.str();
}

// 指定したキーが存在するかどうか
bool HeaderMap::IsKeyExists( const std::string & key ) const
{
	return (this->innerMap.find( key ) != this->innerMap.end());
}

// map のラッピング: 要素の挿入
void HeaderMap::Insert( const std::string & key, const std::string & value )
{
	this->innerMap.insert( std::map<std::string, std::string>::value_type( key, value ) );
}

// map のラッピング: 要素の削除
void HeaderMap::Erase( const std::string & key )
{
	this->innerMap.erase( key );
}

// map のラッピング: [] 演算子によるアクセス
std::string & HeaderMap::operator[]( const std::string & key )
{
	return this->innerMap[key];
}

// [] 演算子によるアクセス const バージョン (map にはない)
const std::string & HeaderMap::operator[]( const std::string & key ) const
{
	return this->innerMap.find( key )->second;
}

// map のラッピング: 要素の全削除
void HeaderMap::Clear()
{
	this->innerMap.clear();
}

// map のラッピング: 先頭をさすイテレータ
HeaderMap::iterator HeaderMap::Begin()
{
	return this->innerMap.begin();
}

// map のラッピング: 先頭をさすイテレータ const バージョン
HeaderMap::const_iterator HeaderMap::Begin() const
{
	return this->innerMap.begin();
}

// map のラッピング: 末尾をさすイテレータ
HeaderMap::iterator HeaderMap::End()
{
	return this->innerMap.end();
}

// map のラッピング: 末尾をさすイテレータ const バージョン
HeaderMap::const_iterator HeaderMap::End() const
{
	return this->innerMap.end();
} 