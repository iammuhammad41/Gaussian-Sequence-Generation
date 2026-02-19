#pragma once
#include "MyDef.h"
#define MSG_STAT WM_USER+1002
// CHWStatView 视图

class CHWStatView : public CView
{
	DECLARE_DYNCREATE(CHWStatView)

protected:
	CHWStatView();           // 动态创建所使用的受保护的构造函数
	virtual ~CHWStatView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	vtkSmartPointer<vtkContextView> view;
	vtkSmartPointer<vtkChartXY> chart;
	vtkSmartPointer<vtkTable> table;
	vtkSmartPointer<vtkFloatArray> arrC;
	vtkSmartPointer<vtkFloatArray> arrS;
	vtkSmartPointer<vtkFloatArray> arrS2;
	vtkSmartPointer<vtkFloatArray> arr1;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	virtual void OnInitialUpdate();
	afx_msg LRESULT OnMsgShow(WPARAM wParam, LPARAM lParam);
	void DrawGussian(std::vector<double>& data);
};


