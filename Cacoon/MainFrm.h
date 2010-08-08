
// MainFrm.h : MainFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once

class MainFrame : public CFrameWndEx
{
private:
	NOTIFYICONDATA m_stNtfyIcon;

protected: // �V���A��������̂ݍ쐬���܂��B
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ����
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �R���g���[�� �o�[�p�����o�[
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnWindowPosChanging(WINDOWPOS * lpwndpos);
	afx_msg void OnCommandMenu_1();
	afx_msg void OnCommandMenu_2();
	afx_msg void OnCommandMenu_3();
	DECLARE_MESSAGE_MAP()

public:
	void OnDestroy(void);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


