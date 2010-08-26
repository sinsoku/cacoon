#include "StdAfx.h"
#include "HeaderMap.h"

// �R���X�g���N�^: ��̃}�b�v���쐬
HeaderMap::HeaderMap()
{
}

// �R���X�g���N�^: �����񂩂�}�b�v���쐬
HeaderMap::HeaderMap( const std::string & headerString )
{
	typedef boost::char_separator<char> Separator;	// ��؂蕶���N���X
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;	// �����N���X

	Separator lineSep( "\r\n" );		// 1 �s���Ƃɋ�؂�
	Tokenizer line( headerString, lineSep );

	Separator elementSep( ":" );		// 1 �s�� : �ŋ�؂�
	Tokenizer::iterator it = line.begin();
	it++;	// 1 �s�ڂ͓ǂݔ�΂��B(���X�|���X�w�b�_�� 2 �s�ڂ���n�܂�)
	for( ; it != line.end(); it++ )
	{
		Tokenizer element( *it, elementSep ); // : �ŋ�؂�
		
		Tokenizer::iterator elemIt = element.begin();

		std::string key = *elemIt++;			// Key �� : ���O
		int spaceCount = 0;	// : �ȍ~�̕�����Ő擪�ɂ���X�y�[�X�̐��𐔂���
		for( std::string::const_iterator it = elemIt->begin(); it != elemIt->end(); it++ )
		{
			if( *it == ' ' )
			{
				spaceCount++;
			}
			else
			{
				break;
			}
		}
		// Value �� : ����̐擪�̃X�y�[�X���폜�������� (�������� 0 �̂Ƃ���X�y�[�X�����Ȃ��Ƃ��͋󕶎��Ƃ���)
		std::string value = (spaceCount != elemIt->length()) ? elemIt->substr( spaceCount ) : "" ;

		this->innerMap.insert( std::map<std::string, std::string>::value_type( key, value ) );	// map �ɓo�^
	}
}

// �}�b�v���當������쐬
std::string HeaderMap::ToString() const
{
	std::ostringstream oss;

	for( std::map<std::string, std::string>::const_iterator it = this->innerMap.begin(); it != this->innerMap.end(); it++ )
	{
		oss << it->first << ": " << it->second << "\r\n";
	}

	return oss.str();
}

// �w�肵���L�[�����݂��邩�ǂ���
bool HeaderMap::IsKeyExists( const std::string & key ) const
{
	return (this->innerMap.find( key ) != this->innerMap.end());
}

// map �̃��b�s���O: �v�f�̑}��
void HeaderMap::Insert( const std::string & key, const std::string & value )
{
	this->innerMap.insert( std::map<std::string, std::string>::value_type( key, value ) );
}

// map �̃��b�s���O: �v�f�̍폜
void HeaderMap::Erase( const std::string & key )
{
	this->innerMap.erase( key );
}

// map �̃��b�s���O: [] ���Z�q�ɂ��A�N�Z�X
std::string & HeaderMap::operator[]( const std::string & key )
{
	return this->innerMap[key];
}

// [] ���Z�q�ɂ��A�N�Z�X const �o�[�W���� (map �ɂ͂Ȃ�)
const std::string & HeaderMap::operator[]( const std::string & key ) const
{
	return this->innerMap.find( key )->second;
}

// map �̃��b�s���O: �v�f�̑S�폜
void HeaderMap::Clear()
{
	this->innerMap.clear();
}

// map �̃��b�s���O: �擪�������C�e���[�^
HeaderMap::iterator HeaderMap::Begin()
{
	return this->innerMap.begin();
}

// map �̃��b�s���O: �擪�������C�e���[�^ const �o�[�W����
HeaderMap::const_iterator HeaderMap::Begin() const
{
	return this->innerMap.begin();
}

// map �̃��b�s���O: �����������C�e���[�^
HeaderMap::iterator HeaderMap::End()
{
	return this->innerMap.end();
}

// map �̃��b�s���O: �����������C�e���[�^ const �o�[�W����
HeaderMap::const_iterator HeaderMap::End() const
{
	return this->innerMap.end();
} 