#pragma once

// �w�b�_���������߂̃N���X�B
// map<string, string> �����b�s���O����B
// map �ɔ�ׂċ@�\�͐�������Ă���
class HeaderMap
{
public:
	// ��̃}�b�v���쐬
	HeaderMap();
	// �w�b�_�����񂩂�}�b�v���쐬
	explicit HeaderMap( const std::string & headerString );

	// �}�b�v����w�b�_������𐶐�
	std::string ToString() const;

	// �w�肵���L�[�����݂��邩�ǂ���
	bool IsKeyExists( const std::string & key ) const;

	// Python �� dict.update �ɑ���
	void Update( const HeaderMap & headerMap );

	// �ȉ��Amap �̃��b�s���O
	typedef std::map<std::string, std::string>::iterator iterator;
	typedef std::map<std::string, std::string>::const_iterator const_iterator;
	void Insert( const std::string & key, const std::string & value );
	void Erase( const std::string & key );
	std::string & operator[]( const std::string & key );
	const std::string & operator[]( const std::string & key ) const;
	void Clear();
	iterator Begin();
	const_iterator Begin() const;
	iterator End();
	const_iterator End() const;

private:
	std::map<std::string, std::string> innerMap;
};

