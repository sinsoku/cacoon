
// CacoonView.cpp : CacoonView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�T���l�C���A����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
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

// CacoonView �R���X�g���N�V����/�f�X�g���N�V����

CacoonView::CacoonView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CacoonView::~CacoonView()
{
}

BOOL CacoonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CacoonView �`��

void CacoonView::OnDraw(CDC* /*pDC*/)
{
	CacoonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
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


// CacoonView �f�f

#ifdef _DEBUG
void CacoonView::AssertValid() const
{
	CView::AssertValid();
}

void CacoonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CacoonDoc* CacoonView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CacoonDoc)));
	return (CacoonDoc*)m_pDocument;
}
#endif //_DEBUG


// CacoonView ���b�Z�[�W �n���h���[
