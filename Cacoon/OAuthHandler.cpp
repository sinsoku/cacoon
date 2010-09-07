#include "StdAfx.h"
#include "OAuthHandler.h"


OAuthHandler::OAuthHandler()
{
}


OAuthHandler::~OAuthHandler()
{
}

std::string OAuthHandler::UrlEncode( const std::string & source )
{
	const char WhiteSpace = ' ';
	const char Period = '.';
	const char Minus = '-';
	const char UnderBar = '_';

	std::ostringstream oss;

	BOOST_FOREACH( const char &c, source )
	{
		if( isalnum( c )
		 || c == Period
		 || c == Minus
		 || c == UnderBar )
		{	// [0-9], [A-Z], [a-z]�A[.], [_], [-] �̂Ƃ��͂��̂܂܏o��
			oss << c;
		}
		else if( c == WhiteSpace )
		{	// ���p�X�y�[�X�� + �ɕϊ�
			oss << '+';
		}
		else
		{	// ���̂ق��� [%16�i] �o��
			oss << '%' << std::hex << std::uppercase << (int)c;
		}
	}

	return oss.str();
}
