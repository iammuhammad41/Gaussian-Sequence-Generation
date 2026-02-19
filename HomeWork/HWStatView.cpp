// HWStatView.cpp: 实现文件
//

#include "pch.h"
#include "HomeWork1.h"
#include "HWStatView.h"
#include "data.h"


// CHWStatView

IMPLEMENT_DYNCREATE(CHWStatView, CView)

CHWStatView::CHWStatView()
{

}

CHWStatView::~CHWStatView()
{
}

BEGIN_MESSAGE_MAP(CHWStatView, CView)
	ON_MESSAGE(MSG_STAT, OnMsgShow)
END_MESSAGE_MAP()


// CHWStatView 绘图

void CHWStatView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CHWStatView 诊断

#ifdef _DEBUG
void CHWStatView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHWStatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHWStatView 消息处理程序


void CHWStatView::PreSubclassWindow()
{
	CView::PreSubclassWindow();
}


void CHWStatView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// TODO: 在此添加专用代码和/或调用基类

}


LRESULT CHWStatView::OnMsgShow(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此处添加实现代码.
	DrawGussian(sortdata);
	UpdateWindow();
	return 0L;
}


void CHWStatView::DrawGussian(std::vector<double>& data)
{
	// TODO: 在此处添加实现代码.
	int status = EXIT_SUCCESS;
	// Set up a 2D scene, add an XY chart to it
	view = vtkSmartPointer<vtkContextView>::New();
	chart = vtkSmartPointer< vtkChartXY>::New();
	table = vtkSmartPointer<vtkTable>::New();
	arrC = vtkSmartPointer<vtkFloatArray>::New();
	arrS = vtkSmartPointer<vtkFloatArray>::New();
	arrS2 = vtkSmartPointer<vtkFloatArray>::New();
	arr1 = vtkSmartPointer<vtkFloatArray>::New();

	CRect rect;
	GetClientRect(rect);
	view->GetRenderWindow()->SetSize(rect.Width(), rect.Height());
	view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	view->GetRenderWindow()->SetMultiSamples(0);

	view->GetScene()->AddItem(chart.GetPointer());

	// Create a table with some points in it...

	arrC->SetName("Cosine");
	table->AddColumn(arrC.GetPointer());

	arrS->SetName("Sine");
	table->AddColumn(arrS.GetPointer());

	arrS2->SetName("Guassian");
	table->AddColumn(arrS2.GetPointer());

	arr1->SetName("One");
	table->AddColumn(arr1.GetPointer());
	// Test charting with a few more points...

	int length = data.size();
	table->SetNumberOfRows(length);

	for (int i = 0; i < length; ++i) {
		double x = data[i];
		double y = gdata[i];

		table->SetValue(i, 0, x);
		table->SetValue(i, 2, y);
	}

	// Add multiple line plots, setting the colors etc

	vtkPlot* line = chart->AddPlot(vtkChart::LINE);
	line->SetInputData(table.GetPointer(), 0, 2);
	line->SetColor(0, 0, 255, 255);
	line->SetWidth(2.0);

	chart->SetShowLegend(true);
	// Render the scene and compare the image to a reference image
	view->GetRenderWindow()->SetParentId(m_hWnd);
	view->GetRenderWindow()->GetInteractor()->Initialize();
	view->GetRenderWindow()->Render();
}
