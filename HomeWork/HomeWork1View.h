
// HomeWork1View.h: CHomeWork1View 类的接口
//

#pragma once
#include "MyDef.h"
#define MSG_AC WM_USER+1003

class CHomeWork1View : public CListView
{
protected: // 仅从序列化创建
	CHomeWork1View() noexcept;
	DECLARE_DYNCREATE(CHomeWork1View)

// 特性
public:
	CHomeWork1Doc* GetDocument() const;

// 操作
public:
	vtkSmartPointer<vtkContextView> view;
	vtkSmartPointer<vtkChartXY> chart;
	vtkSmartPointer<vtkTable> table;

	vtkSmartPointer<vtkDoubleArray> arrI;
	vtkSmartPointer<vtkDoubleArray> arrX;
	vtkSmartPointer<vtkDoubleArray> arrY;
	//int CreateDisplay();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CHomeWork1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	//afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT CHomeWork1View::OnMsgShow(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	int DrawAC(std::vector<double>& data);
};

#ifndef _DEBUG  // HomeWork1View.cpp 中的调试版本
inline CHomeWork1Doc* CHomeWork1View::GetDocument() const
   { return reinterpret_cast<CHomeWork1Doc*>(m_pDocument); }
#endif

