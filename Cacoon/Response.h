#pragma once

class HeaderMap;

// HTTP のサーバーからのレスポンスを表すクラス
class Response
{
public:
	// サーバーから返った生の文字列からレスポンスを作成する
	explicit Response( const std::string & rawResponse );

	int StatusCode();
	const HeaderMap & Header();
	const std::string & Body();

private:

	int statusCode;
	boost::shared_ptr<HeaderMap> header;
	std::string body;
};
