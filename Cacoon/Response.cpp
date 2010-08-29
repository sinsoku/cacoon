#include "stdafx.h"
#include "Response.h"
#include "HeaderMap.h"
// �R���X�g���N�^
Response::Response( const std::string & rawResponse )
{
	if( rawResponse.length() < 13 )
	{
		throw CACOON_EXCEPTION( "���X�|���X�����񂪕s���ł�" );
	}
	const int StatusOffset = 9;	// �X�e�[�^�X�R�[�h�̓��X�|���X�w�b�_�� 9 �����ڂ���n�܂�B
	char statusCodeAsString[4];

	for( int i=0; i<3; i++ )
	{
		statusCodeAsString[i] = rawResponse[i+StatusOffset];
	}
	statusCodeAsString[3] = '\0';

	this->statusCode = boost::lexical_cast<int, char *>( statusCodeAsString );

	int endOfFirstLine = rawResponse.find( "\r\n" );	// �ŏ��̃��X�|���X�s�͖�������B
	int headerOffset = rawResponse.find( "\r\n\r\n" );	// �w�b�_�͍ŏ��� CR LF CR LF �܂�

	if( endOfFirstLine == std::string::npos || headerOffset == std::string::npos )
	{
		throw CACOON_EXCEPTION( "�T�[�o�[����̃��X�|���X������܂���ł���" );
	}
	// ���X�|���X�s�� CRLF ���܂܂��A�w�b�_�Ƃ̋�؂�� CRLF ����܂ށB
	this->header = boost::shared_ptr<HeaderMap>( new HeaderMap( rawResponse.substr( endOfFirstLine+2, headerOffset-endOfFirstLine ) ) );
	// �w�b�_�Ƃ̋�؂�� CRLF �͊܂܂Ȃ��B
	this->body = rawResponse.substr( headerOffset+4 );
}


// �Q�b�^�[
int Response::StatusCode()
{
	return this->statusCode;
}

const HeaderMap & Response::Header()
{
	return *this->header;
}

const std::string & Response::Body()
{
	return this->body;
}