#pragma once

// HTTP のサーバーからのレスポンスを表すクラス
class Response
{
public:
	// サーバーから返った生の文字列からレスポンスを作成する
	Response( const std::string & rawResponse );

	int StatusCode();
	const std::string & Header();
	const std::string & Body();
	
private:

	int statusCode;
	std::string header;
	std::string body;
};
