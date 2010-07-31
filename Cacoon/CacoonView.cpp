
// CacoonView.cpp : CacoonView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "Cacoon.h"
#endif

#include "CacoonDoc.h"
#include "CacoonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CacoonView

IMPLEMENT_DYNCREATE(CacoonView, CView)

BEGIN_MESSAGE_MAP(CacoonView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CacoonView コンストラクション/デストラクション

CacoonView::CacoonView()
{
	// TODO: 構築コードをここに追加します。

}

CacoonView::~CacoonView()
{
}

BOOL CacoonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CacoonView 描画

void CacoonView::OnDraw(CDC* /*pDC*/)
{
	CacoonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

void CacoonView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CacoonView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CacoonView 診断

#ifdef _DEBUG
void CacoonView::AssertValid() const
{
	CView::AssertValid();
}

void CacoonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CacoonDoc* CacoonView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CacoonDoc)));
	return (CacoonDoc*)m_pDocument;
}
#endif //_DEBUG


// CacoonView メッセージ ハンドラー
