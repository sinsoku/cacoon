#pragma once

// HTTP �̃T�[�o�[����̃��X�|���X��\���N���X
class Response
{
public:
	// �T�[�o�[����Ԃ������̕����񂩂烌�X�|���X���쐬����
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
