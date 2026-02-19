// HWAnaView.cpp: 实现文件
//

#include "pch.h"
#include "HomeWork1.h"
#include "HWAnaView.h"
#include"data.h"

// CHWAnaView

IMPLEMENT_DYNCREATE(CHWAnaView, CView)

CHWAnaView::CHWAnaView()
{

}
int CHWAnaView::DrawSine(std::vector<double>& data)
{
	// TODO: 在此添加专用代码和/或调用基类
	int status = EXIT_SUCCESS;
	// Set up a 2D scene, add an XY chart to it
	view = vtkSmartPointer<vtkContextView>::New();
	chart = vtkSmartPointer< vtkChartXY>::New();
	table = vtkSmartPointer<vtkTable>::New();
	
	arrI = vtkSmartPointer<vtkDoubleArray>::New();
	arrX = vtkSmartPointer<vtkDoubleArray>::New();
	arrY = vtkSmartPointer<vtkDoubleArray>::New();

	CRect rect;
	GetClientRect(rect);
	view->GetRenderWindow()->SetSize(rect.Width(), rect.Height());
	view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	view->GetRenderWindow()->SetMultiSamples(0);

	view->GetScene()->AddItem(chart.GetPointer());

	// 设置小标题
	arrI->SetName("Gauss Normal Random I");
	table->AddColumn(arrI.GetPointer());

	arrX->SetName("Gauss Normal Random X");
	table->AddColumn(arrX.GetPointer());
	
	arrY->SetName("Gauss Normal Random Y");
	table->AddColumn(arrY.GetPointer());

	// Test charting with a few more points...
	int length = data.size();
	table->SetNumberOfRows(length);
	for (int i = 0; i < length; ++i) {
		double x = data1[i];
		table->SetValue(i, 0, double(i));
		table->SetValue(i, 1, x);
	}

	vtkPlot* line = chart->AddPlot(vtkChart::POINTS);
	line->SetInputData(table.GetPointer(), 0, 1);
	line->SetColor(0, 255, 0, 255);
	line->SetWidth(2.0);

	chart->SetShowLegend(true);
	// Render the scene and compare the image to a reference image
	view->GetRenderWindow()->SetParentId(m_hWnd);
	view->GetRenderWindow()->GetInteractor()->Initialize();
	view->GetRenderWindow()->Render();

    return 0;
}

CHWAnaView::~CHWAnaView()
{
}

BEGIN_MESSAGE_MAP(CHWAnaView, CView)
	ON_MESSAGE(MSG_SHOW, OnMsgShow)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHWAnaView 绘图

void CHWAnaView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CHWAnaView 诊断

#ifdef _DEBUG
void CHWAnaView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHWAnaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHWAnaView 消息处理程序


void CHWAnaView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类
    //DrawSine(data1,100,10,3);
}


LRESULT CHWAnaView::OnMsgShow(WPARAM wParam,LPARAM lParam)
{
	// TODO: 在此处添加实现代码.
	DrawSine(data2);
	UpdateWindow();
	return 0L;
}


void CHWAnaView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()
}
