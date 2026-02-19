
// HomeWork1View.cpp: CHomeWork1View 类的实现
//

#include "pch.h"
#include "MyDef.h"
#include "data.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomeWork1View

IMPLEMENT_DYNCREATE(CHomeWork1View, CListView)

BEGIN_MESSAGE_MAP(CHomeWork1View, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_MESSAGE(MSG_AC, OnMsgShow)
END_MESSAGE_MAP()

// CHomeWork1View 构造/析构

CHomeWork1View::CHomeWork1View() noexcept
{
	// TODO: 在此处添加构造代码
}

CHomeWork1View::~CHomeWork1View()
{
}

BOOL CHomeWork1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CHomeWork1View::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，

}

void CHomeWork1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHomeWork1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

LRESULT CHomeWork1View::OnMsgShow(WPARAM wParam, LPARAM lParam)
{
    DrawAC(acdata);
    UpdateWindow();
    return 0L;
}


// CHomeWork1View 诊断

#ifdef _DEBUG
void CHomeWork1View::AssertValid() const
{
	CListView::AssertValid();
}

void CHomeWork1View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CHomeWork1Doc* CHomeWork1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomeWork1Doc)));
	return (CHomeWork1Doc*)m_pDocument;
}
#endif //_DEBUG


// CHomeWork1View 消息处理程序
void CHomeWork1View::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: 添加代码以响应用户对窗口视图样式的更改
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);
}


int CHomeWork1View::DrawAC(std::vector<double>& data)
{
    // TODO: 在此处添加实现代码.
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

    // Create a table with some points in it...
    arrI->SetName("Gauss Normal Random I");
    table->AddColumn(arrI.GetPointer());

    arrX->SetName("Autocorrelation Function");
    table->AddColumn(arrX.GetPointer());

    arrY->SetName("Gauss Normal Random Y");
    table->AddColumn(arrY.GetPointer());

    // Test charting with a few more points...
    int length = data.size();
    table->SetNumberOfRows(2 * static_cast<vtkIdType>(length) - 1);

    for (int i = 1; i < length; ++i) {
        table->SetValue(static_cast<vtkIdType>(i)-1, 0, double(i-length));
        table->SetValue(static_cast<vtkIdType>(i)-1, 1, data[length-i]);
    }
    for (int i = 0; i < length; ++i) {
        table->SetValue(static_cast<vtkIdType>(i)+length-1, 0, double(i));
        table->SetValue(static_cast<vtkIdType>(i)+length-1 , 1, data[i]);
    }


    vtkPlot* line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table.GetPointer(), 0, 1);
    line->SetColor(255, 0, 0, 255);
    line->SetWidth(2.0);

    chart->SetShowLegend(true);
    // Render the scene and compare the image to a reference image
    view->GetRenderWindow()->SetParentId(m_hWnd);
    view->GetRenderWindow()->GetInteractor()->Initialize();
    view->GetRenderWindow()->Render();
    return 0;
}
