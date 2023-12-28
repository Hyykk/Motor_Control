// GraphDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotExp_4.h"
#include "GraphDlg.h"
#include "afxdialogex.h"
#include "SystemMemory.h"
#include "DataType.h"

// CGraphDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAPH_DIALOG, pParent)
{

}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NTGRAPH_POS, m_ntgPos);
	DDX_Control(pDX, IDC_NTGRAPH_VEL, m_ntgVel);
	DDX_Control(pDX, IDC_NTGRAPH_TORQ, m_ntgTorque);
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGraphDlg 메시지 처리기입니다.


void CGraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_dCnt += 0.1;
	DataType_t jointData;
	ControlData_t graphData;
	double tar_ode_angle;
	GET_SYSTEM_MEMORY("JointData", jointData);

	if (m_dCnt >= 10.0)
	{
		m_ntgPos.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 360.0);
		m_ntgVel.SetRange(m_dCnt - 10.0, m_dCnt, -30.0, 30.0);
		m_ntgTorque.SetRange(m_dCnt - 10.0, m_dCnt, -0.5, 0.5);
	}

	if (jointData.Q_tar[1] < 0) {
		tar_ode_angle = 360 + jointData.Q_tar[1];
	}
	else {
		tar_ode_angle = jointData.Q_tar[1];
	}

	m_ntgPos.PlotXY(m_dCnt, tar_ode_angle, 1);
	m_ntgPos.PlotXY(m_dCnt, CurPos, 2);
	m_ntgVel.PlotXY(m_dCnt, TarVelo , 1);
	m_ntgVel.PlotXY(m_dCnt, CurVelo, 2);
	m_ntgTorque.PlotXY(m_dCnt, TarTorq, 1);
	m_ntgTorque.PlotXY(m_dCnt, CurTorq, 2);

	CDialogEx::OnTimer(nIDEvent);
}

void CGraphDlg::InitNTGraph()
{
	m_ntgPos.ClearGraph();
	m_ntgVel.ClearGraph();
	m_ntgTorque.ClearGraph();

	m_ntgPos.SetFrameStyle(0);
	m_ntgVel.SetFrameStyle(0);
	m_ntgTorque.SetFrameStyle(0);

	m_ntgPos.SetPlotAreaColor(WHITE);
	m_ntgVel.SetPlotAreaColor(WHITE);
	m_ntgTorque.SetPlotAreaColor(WHITE);

	m_ntgPos.SetShowGrid(TRUE);
	m_ntgVel.SetShowGrid(TRUE);
	m_ntgTorque.SetShowGrid(TRUE);

	m_ntgPos.SetFormatAxisBottom(_T("%.2f"));
	m_ntgVel.SetFormatAxisBottom(_T("%.2f"));
	m_ntgTorque.SetFormatAxisBottom(_T("%.2f"));

	m_ntgPos.SetCaption("위치");
	m_ntgVel.SetCaption("속도");
	m_ntgTorque.SetCaption("토크");

	m_ntgPos.SetXLabel("Time[s]");
	m_ntgVel.SetXLabel("Time[s]");
	m_ntgTorque.SetXLabel("Time[s]");

	m_ntgPos.SetYLabel("Degree[deg]");
	m_ntgVel.SetYLabel("Velocity[deg/s]");
	m_ntgTorque.SetYLabel("Torque[Nm]");

	m_ntgPos.AddElement();
	m_ntgPos.SetElementWidth(4);
	m_ntgPos.SetElementLineColor(RED);
	m_ntgPos.AddElement();
	m_ntgPos.SetElementWidth(3);
	m_ntgPos.SetElementLineColor(BLUE);

	m_ntgPos.SetRange(0.0, 10.0, 0.0, 360.0);
	m_ntgPos.SetYGridNumber(4);

	m_ntgVel.AddElement();
	m_ntgVel.SetElementWidth(4);
	m_ntgVel.SetElementLineColor(RED);
	m_ntgVel.AddElement();
	m_ntgVel.SetElementWidth(3);
	m_ntgVel.SetElementLineColor(BLUE);
	m_ntgVel.SetRange(0.0, 10.0, -30.0, 30.0);

	m_ntgTorque.AddElement();
	m_ntgTorque.SetElementWidth(4);
	m_ntgTorque.SetElementLineColor(RED);
	m_ntgTorque.AddElement();
	m_ntgTorque.SetElementWidth(3);
	m_ntgTorque.SetElementLineColor(BLUE);
	m_ntgTorque.SetRange(0.0, 10.0, -0.5, 0.5);

	SetTimer(1, 100, NULL);

}


BOOL CGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitNTGraph();

	return TRUE;
	// return TRUE unless you set the force to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
