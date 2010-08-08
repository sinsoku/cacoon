
// MainFrm.h : MainFrame クラスのインターフェイス
//

#pragma once

class MainFrame : public CFrameWndEx
{
private:
	NOTIFYICONDATA m_stNtfyIcon;

protected: // シリアル化からのみ作成します。
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 実装
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバー
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// 生成された、メッセージ割り当て関数
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


