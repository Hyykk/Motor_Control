#pragma once
#include "NTGraph.h"
// #include "COCX.h"

#define RED      RGB(127, 0, 0)
#define GREEN   RGB(0, 127, 0)
#define BLUE   RGB(0, 0, 127)
#define BLACK   RGB(0, 0, 0)
#define WHITE   RGB(255, 255, 255)
#define GRAY   RGB(192, 192, 192)

#define DEG2RAD 0.0174533   // 각도를 라디안으로
#define RAD2DEG 57.2958      // 라디안을 각도로


// CGraphDlg 대화 상자입니다.

class CGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphDlg)

public:
	CGraphDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGraphDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void InitNTGraph();

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	double m_dCnt = 0;
	CNTGraph m_ntgPos;
	CNTGraph m_ntgVel;
	CNTGraph m_ntgTorque;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
