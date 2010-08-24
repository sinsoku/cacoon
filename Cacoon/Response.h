#pragma once

// HTTP のサーバーからのレスポンスを表すクラス
class Response
{
public:
	// サーバーから返った生の文字列からレスポンスを作成する
	explicit Response( const std::string & rawResponse );

	int StatusCode();
	const std::string & Header();
	const std::string & Body();

	typedef std::map<std::string, std::string> HeaderMap;
	static void HeaderToMap( const std::string & header, HeaderMap * pMapOut );
	static void MapToHeader( const HeaderMap & map, std::string * pHeaderOut );

private:

	int statusCode;
	std::string header;
	std::string body;
};
