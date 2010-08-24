#pragma once

// ヘッダを扱うためのクラス。
// map<string, string> をラッピングする。
// map に比べて機能は制限されている
class HeaderMap
{
public:
	// 空のマップを作成
	HeaderMap();
	// ヘッダ文字列からマップを作成
	explicit HeaderMap( const std::string & headerString );

	// マップからヘッダ文字列を生成
	std::string ToString() const;

	// 指定したキーが存在するかどうか
	bool IsKeyExists( const std::string & key );

	// 以下、map のラッピング
	typedef std::map<std::string, std::string>::iterator iterator;
	typedef std::map<std::string, std::string>::const_iterator const_iterator;
	void Insert( const std::string & key, const std::string & value );
	void Erase( const std::string & key );
	std::string & operator[]( const std::string & key );
	void Clear();
	iterator Begin();
	const_iterator Begin() const;
	iterator End();
	const_iterator End() const;

private:
	std::map<std::string, std::string> innerMap;
};

