// ParamsView.cpp: 实现文件
//

#include "pch.h"
#include "MyDef.h"
#include "data.h"
#include "HomeWork1.h"
#include "ParamsView.h"
#include "MainFrm.h"


CEvent evtStart;
CEvent evtPause;
CEvent evtRunning;
CEvent evtStop;
CEvent evtcapture;
CEvent evtCal;
CEvent evtDuel;


HANDLE evts[2] = { evtStop,evtPause };

BOOL m_pause = FALSE;
CaptureParams m_cap;
CalculateParams m_cal;
UINT __cdecl ThreadCapture(_In_ LPVOID lpParameter);
UINT __cdecl ThreadCalculate(_In_ LPVOID lpParameter);

// CParamsView


IMPLEMENT_DYNCREATE(CParamsView, CFormView)

CParamsView::CParamsView()
	: CFormView(IDD_CParamsView)
{

}

CParamsView::~CParamsView()
{
}

void CParamsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CParamsView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CParamsView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CParamsView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CParamsView::OnBnClickedButton3)
END_MESSAGE_MAP()


// CParamsView 诊断

#ifdef _DEBUG
void CParamsView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CParamsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CParamsView 消息处理程序


void CParamsView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
	CParamsView* pMA=((CMainFrame*)AfxGetMainWnd())->GetLeftPane();
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	CMainFrame* pMF = (CMainFrame*)AfxGetMainWnd();
	m_cal.pAna = pMF->GetAnaPane();
	m_cal.pHw = pMF->GetHWPane();
	m_cal.pStat = pMF->GetStatPane();
	if (m_pause) 
	{
		evtPause.ResetEvent();
		evtRunning.SetEvent();
	}
	else {
		CString m_str1, m_str2, m_str3, m_str4;
		GetDlgItem(IDC_EDIT1)->GetWindowTextW(m_str1);
		GetDlgItem(IDC_EDIT2)->GetWindowTextW(m_str2);
		GetDlgItem(IDC_EDIT3)->GetWindowTextW(m_str3);
		GetDlgItem(IDC_EDIT4)->GetWindowTextW(m_str4);
		m_mean = _tstoi(m_str1);
		m_cov = _tstoi(m_str2);
		m_length = _tstoi(m_str3);
		m_update = _tstoi(m_str4);
		GetDlgItem(IDC_BUTTON3)->EnableWindow();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(0);

		evtStart.SetEvent();
		evtRunning.SetEvent();
		evtPause.ResetEvent();
		evtStop.ResetEvent();
		evtCal.SetEvent();
		
		
		m_cap.m_cov = m_cov;
		m_cap.m_mean = m_mean;
		m_cap.m_length = m_length;
		m_cap.m_update = m_update;
		m_cap.pView = this;

		AfxBeginThread(ThreadCapture, (LPVOID)&m_cap);
		AfxBeginThread(ThreadCalculate, (LPVOID)&m_cal);

	}
	
}

void CParamsView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	evtPause.SetEvent();
	evtRunning.ResetEvent();
	m_pause = TRUE;
	GetDlgItem(IDC_BUTTON1)->EnableWindow();
	GetDlgItem(IDC_BUTTON3)->EnableWindow(0);

}

void CParamsView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pause = FALSE;
	evtStop.SetEvent();
	GetDlgItem(IDC_BUTTON1)->EnableWindow();
	GetDlgItem(IDC_BUTTON3)->EnableWindow(0);
}



UINT __cdecl ThreadCapture(_In_ LPVOID lpParameter)
{
	CaptureParams* pCap = (CaptureParams*)lpParameter;
	DWORD hwd=::WaitForSingleObject(evtStart, INFINITY);

	std::default_random_engine generator;
	std::normal_distribution<double> dist(pCap->m_mean, pCap->m_cov);

	data1.clear();
	int a = m_length / 10;
	for (int i = 0; i < pCap->m_length; i++,a++) {
		DWORD dwRet = ::WaitForMultipleObjects(2, evts, FALSE, 0);
		if (dwRet == WAIT_OBJECT_0) {
			AfxEndThread(100, TRUE);
		}
		if (dwRet == WAIT_OBJECT_0 + 1)
		{
			::WaitForSingleObject(evtRunning, INFINITY);
		}
		::WaitForSingleObject(evtCal, INFINITY);
		double d = dist(generator);
		evtcapture.ResetEvent();
		data1.push_back(d);
		evtcapture.SetEvent();

		if (a %(m_length/10)==1) {
			evtDuel.SetEvent();
			Sleep(1000/m_update);
		}
	}
	evtDuel.SetEvent();
	pCap->pView->GetDlgItem(IDC_BUTTON1)->EnableWindow();
	pCap->pView->GetDlgItem(IDC_BUTTON3)->EnableWindow(0);
	return 0;
}

UINT __cdecl ThreadCalculate(_In_ LPVOID lpParameter)
{
	CalculateParams* pCap = (CalculateParams*)lpParameter;
	while (1) {

		DWORD hw = ::WaitForSingleObject(evtDuel, 10000);
		if (hw == WAIT_OBJECT_0) {
			evtDuel.ResetEvent();
		}
		else if (hw == WAIT_TIMEOUT) {
			AfxEndThread(100, TRUE);
		}
		DWORD hwd = ::WaitForSingleObject(evtcapture, 50);
		if (hwd == WAIT_TIMEOUT) 
		{
			AfxEndThread(100, TRUE);
		}
		evtCal.ResetEvent();
		SortData(data1, sortdata);//高斯输出
		ACData(data1, acdata);
		evtCal.SetEvent();
		evtDuel.ResetEvent();

		HWND m_hwd = pCap->pAna->GetSafeHwnd();
		HWND m_hwd1 = pCap->pStat->GetSafeHwnd();
		HWND m_hwd2 = pCap->pHw->GetSafeHwnd();

		::SendMessage(m_hwd, MSG_SHOW, 0, 0);
		::SendMessage(m_hwd1, MSG_STAT, 0, 0);
		::SendMessage(m_hwd2, MSG_AC, 0, 0);

	}
	return 0;
}


void CParamsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(L"0");//设置均值默认值
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(L"10");//设置方差默认值
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(L"1000");//设置点数默认值
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(L"1");//设置每秒默认刷新次数
	evtDuel.ResetEvent();
	evtcapture.ResetEvent();
}
