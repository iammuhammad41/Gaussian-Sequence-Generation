#pragma once



// CParamsView 窗体视图

class CParamsView : public CFormView
{
	DECLARE_DYNCREATE(CParamsView)

protected:
	CParamsView();           // 动态创建所使用的受保护的构造函数
	virtual ~CParamsView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CParamsView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	virtual void OnInitialUpdate();
};


