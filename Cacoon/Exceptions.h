#pragma once



// ���ʂ̗�O�N���X�B
// �Ǝ��̗�O���`����ꍇ�͂��̃N���X����h��������B
class CacoonExceptionBase
{
public:
	// ���ʗ�O�N���X�̃R���X�g���N�^
	// message  : �G���[�̓��e��\��������
	// __file__ : �G���[�̔��������\�[�X�t�@�C��
	// __line__ : �G���[�̔��������s
	CacoonExceptionBase();
};

//#define CacoonException( message ) CacoonExceptionBase( message )