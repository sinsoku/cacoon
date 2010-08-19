#pragma once

// HTTP �̃T�[�o�[����̃��X�|���X��\���N���X
class Response
{
public:
	// �T�[�o�[����Ԃ������̕����񂩂烌�X�|���X���쐬����
	Response( const std::string & rawResponse );

	int StatusCode();
	const std::string & Header();
	const std::string & Body();
	
private:

	int statusCode;
	std::string header;
	std::string body;
};
