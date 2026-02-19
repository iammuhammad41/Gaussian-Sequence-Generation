#ifndef _EX_SPLITTER_WND
#define _EX_SPLITTER_WND
#pragma once
#include <afxext.h>
#define CX_BORDER 1
#define CY_BORDER 1
class CExSplitterWnd :public CSplitterWnd
{
public:

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	virtual void OnInvertTracker(const CRect& rect);
};

#endif
