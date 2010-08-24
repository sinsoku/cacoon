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

	if( headerOffset == std::string::npos )
	{
		throw CACOON_EXCEPTION( "�T�[�o�[����̃��X�|���X������܂���ł���" );
	}

	this->header = rawResponse.substr( 0, headerOffset+2 );	// �w�b�_�Ƃ̋�؂�� CRLF ����܂ށB
	this->body = rawResponse.substr( headerOffset+4 );		// �w�b�_�Ƃ̋�؂�� CRLF �͊܂܂Ȃ��B
}
// �w�b�_������ std::map �ւ̕ϊ�
void Response::HeaderToMap( const std::string & header, HeaderMap * pMapOut )
{
	pMapOut->clear();	// �O�̂��ߗv�f���폜

	typedef boost::char_separator<char> Separator;	// ��؂蕶���N���X
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;	// �����N���X

	Separator lineSep( "\r\n" );		// 1 �s���Ƃɋ�؂�
	Tokenizer line( header, lineSep );

	Separator elementSep( ":" );		// 1 �s�� : �ŋ�؂�

	for( auto it = line.begin(); it != line.end(); it++ )
	{
		Tokenizer element( *it, elementSep );
		
		auto elemIt = element.begin();

		std::string key = *elemIt++;			// : ���O
		std::string val = elemIt->substr( 1 );	// : ����

		(*pMapOut)[key] = val;	// map �ɓo�^
	}
}

// std::map �� �w�b�_������ւ̕ϊ�
void Response::MapToHeader( const HeaderMap & map, std::string * pHeaderOut )
{
	pHeaderOut->clear();	// �O�̂��ߍ폜

	std::ostringstream oss;

	for( auto it = map.begin(); it != map.end(); it++ )
	{
		oss << it->first << ": " << it->second << "\r\n";
	}

	//pHeaderOut
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