
// Cacoon.h : Cacoon �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CacoonApp:
// ���̃N���X�̎����ɂ��ẮACacoon.cpp ���Q�Ƃ��Ă��������B
//

class CacoonApp : public CWinAppEx
{
public:
	CacoonApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CacoonApp theApp;
