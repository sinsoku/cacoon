#pragma once

class HeaderMap;

// HTTP �̃T�[�o�[����̃��X�|���X��\���N���X
class Response
{
public:
	// �T�[�o�[����Ԃ������̕����񂩂烌�X�|���X���쐬����
	explicit Response( const std::string & rawResponse );

	int StatusCode();
	const HeaderMap & Header();
	const std::string & Body();

private:

	int statusCode;
	boost::shared_ptr<HeaderMap> header;
	std::string body;
};
