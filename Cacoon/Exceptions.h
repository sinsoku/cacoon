#pragma once



// 共通の例外クラス。
// 独自の例外を定義する場合はこのクラスから派生させる。
class CacoonExceptionBase
{
public:
	// 共通例外クラスのコンストラクタ
	// message  : エラーの内容を表す文字列
	// __file__ : エラーの発生したソースファイル
	// __line__ : エラーの発生した行
	CacoonExceptionBase();
};

//#define CacoonException( message ) CacoonExceptionBase( message )