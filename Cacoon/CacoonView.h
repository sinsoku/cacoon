
// CacoonView.h : CacoonView クラスのインターフェイス
//

#pragma once


class CacoonView : public CView
{
protected: // シリアル化からのみ作成します。
	CacoonView();
	DECLARE_DYNCREATE(CacoonView)

// 属性
public:
	CacoonDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CacoonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CacoonView.cpp のデバッグ バージョン
inline CacoonDoc* CacoonView::GetDocument() const
   { return reinterpret_cast<CacoonDoc*>(m_pDocument); }
#endif

