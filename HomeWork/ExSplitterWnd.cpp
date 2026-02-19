#include "pch.h"
#include "ExSplitterWnd.h"
BEGIN_MESSAGE_MAP(CExSplitterWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


void CExSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//封锁拖拽功能
	CSplitterWnd::OnLButtonDown(nFlags, point);
}

void CExSplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CSplitterWnd::OnMouseMove(nFlags, point);
	//封锁拖拽功能
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CExSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//改为调用CWnd的OnSetCursor函数，封锁拖拽功能
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
	//return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CExSplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
	// TODO: 在此添加专用代码和/或调用基类
    if (pDC == NULL)
    {
        RedrawWindow(rectArg, NULL, RDW_INVALIDATE | RDW_NOCHILDREN);
        return;
    }
    ASSERT_VALID(pDC);
    CRect rc = rectArg;
    switch (nType)
    {
    case splitBorder:
        //重画分割窗口边界,使之为红色 
        pDC->Draw3dRect(rc, RGB(255, 0, 0), RGB(255, 0, 0));
        rc.InflateRect(-CX_BORDER, -CY_BORDER);
        pDC->Draw3dRect(rc, RGB(255, 0, 0), RGB(255, 0, 0));

        return;
    case splitBox:
        pDC->Draw3dRect(rc, RGB(0, 0, 0), RGB(0, 0, 0));
        rc.InflateRect(-CX_BORDER, -CY_BORDER);
        pDC->Draw3dRect(rc, RGB(0, 0, 0), RGB(0, 0, 0));
        rc.InflateRect(-CX_BORDER, -CY_BORDER);
        pDC->FillSolidRect(rc, RGB(0, 0, 0));
        pDC->Draw3dRect(rc, RGB(0, 0, 0), RGB(0, 0, 0));
        return;
    case splitBar:
        //重画分割条，使之为绿色 
        pDC->FillSolidRect(rc, RGB(255, 255, 255));
        rc.InflateRect(-5, -5);
        pDC->Draw3dRect(rc, RGB(255, 0, 0), RGB(255, 0, 0));

        return;
    default:
        ASSERT(FALSE);
    }
    pDC->FillSolidRect(rc, RGB(0, 0, 255));
	//CSplitterWnd::OnDrawSplitter(pDC, nType, rectArg);
}


void CExSplitterWnd::OnInvertTracker(const CRect& rect)
{
	// TODO: 在此添加专用代码和/或调用基类
    ASSERT_VALID(this);
    ASSERT(!rect.IsRectEmpty());
    ASSERT((GetStyle() & WS_CLIPCHILDREN) == 0);
    CRect rc = rect;
    rc.InflateRect(2, 2);
    CDC* pDC = GetDC();
    CBrush* pBrush = CDC::GetHalftoneBrush();
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL) hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
    pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), BLACKNESS);

    if (hOldBrush != NULL)
        SelectObject(pDC->m_hDC, hOldBrush);
    ReleaseDC(pDC);
	//CSplitterWnd::OnInvertTracker(rect);
}
