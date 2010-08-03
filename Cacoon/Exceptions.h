#pragma once

// ��O�̔��������t�@�C�����ƍs�����擾���邽�߂̃}�N��
#define CACOON_EXCEPTION( message ) CacoonException( message, __FILE__, __LINE__ )

// ���ʂ̗�O�N���X�B
// �Ǝ��̗�O���`����ꍇ�͂��̃N���X����h��������B
class CacoonException : public std::exception
{
public:
	// ���ʗ�O�N���X�̃R���X�g���N�^
	// message  : �G���[�̓��e��\��������
	// __file__ : �G���[�̔��������\�[�X�t�@�C��
	// __line__ : �G���[�̔��������s
	CacoonException( const char * message, const char * __file__, int __line__ );

	// ��O�̓��e�� string �Ŏ擾����
	std::string Info() const;
	
private:
	std::string info;
};
