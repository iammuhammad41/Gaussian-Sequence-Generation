#pragma once

#include "MyDef.h"
#define MSG_SHOW WM_USER+1001
// CHWAnaView 视图

class CHWAnaView : public CView
{
	DECLARE_DYNCREATE(CHWAnaView)

protected:
	CHWAnaView();           // 动态创建所使用的受保护的构造函数
	virtual ~CHWAnaView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	vtkSmartPointer<vtkContextView> view;
	vtkSmartPointer<vtkChartXY> chart;
	vtkSmartPointer<vtkTable> table;

	vtkSmartPointer<vtkDoubleArray> arrI;
	vtkSmartPointer<vtkDoubleArray> arrX;
	vtkSmartPointer<vtkDoubleArray> arrY;
	int DrawSine(std::vector<double>& data);
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg LRESULT CHWAnaView::OnMsgShow(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
};


