#include "stdafx.h"
#include "Response.h"

// �R���X�g���N�^
Response::Response( const std::string & rawResponse )
{
	const int StatusOffset = 9;	// �X�e�[�^�X�R�[�h�̓��X�|���X�w�b�_�� 9 �����ڂ���n�܂�B
	char statusCodeAsString[4];

	for( int i=0; i<3; i++ )
	{
		statusCodeAsString[i] = rawResponse[i+StatusOffset];
	}
	statusCodeAsString[3] = '\0';

	this->statusCode = atoi( statusCodeAsString );

	int headerOffset = rawResponse.find( "\r\n\r\n" );	// �w�b�_�͍ŏ��� CR LF CR LF �܂�

	this->header = rawResponse.substr( 0, headerOffset+2 );	// �w�b�_�Ƃ̋�؂�� CRLF ����܂ށB
	this->body = rawResponse.substr( headerOffset+4 );		// �w�b�_�Ƃ̋�؂�� CRLF �͊܂܂Ȃ��B

}


// �Q�b�^�[
int Response::StatusCode()
{
	return this->statusCode;
}

const std::string & Response::Header()
{
	return this->header;
}

const std::string & Response::Body()
{
	return this->body;
}