#pragma once

// 例外の発生したファイル名と行数を取得するためのマクロ
#define CACOON_EXCEPTION( message ) CacoonException( message, __FILE__, __LINE__ )

// 共通の例外クラス。
// 独自の例外を定義する場合はこのクラスから派生させる。
class CacoonException : public std::exception
{
public:
	// 共通例外クラスのコンストラクタ
	// message  : エラーの内容を表す文字列
	// __file__ : エラーの発生したソースファイル
	// __line__ : エラーの発生した行
	CacoonException( const char * message, const char * __file__, int __line__ );

	// 例外の内容を string で取得する
	std::string Info() const;
	
private:
	std::string info;
};
