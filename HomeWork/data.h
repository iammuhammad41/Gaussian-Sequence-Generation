#pragma once
#include "ParamsView.h"
#include"MyDef.h"
extern int m_mean;
extern int m_cov;
extern int m_length;
extern int m_update;

struct CaptureParams {
	CParamsView* pView;
	int m_mean;
	int m_cov;
	int m_length;
	int m_update;
};
struct CalculateParams {
	CHWAnaView* pAna;
	CHWStatView* pStat;
	CHomeWork1View* pHw;

};