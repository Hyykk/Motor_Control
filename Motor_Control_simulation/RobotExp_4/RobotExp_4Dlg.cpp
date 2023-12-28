
// RobotExp_4Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RobotExp_4.h"
#include "RobotExp_4Dlg.h"

#include "ThreadWorker.h"
#include "WorkBase.h"
#include "ODEWork.h"

#include "SystemMemory.h"
#include "DataType.h"

#include "afxdialogex.h"
#include "DataType.h"

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double TarVelo = 0.;
double TarTorq = 0.;
double CurVelo = 0.;
double CurTorq = 0.;
double CurPos = 0.;


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRobotExp_4Dlg ��ȭ ����



CRobotExp_4Dlg::CRobotExp_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROBOTEXP_4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRobotExp_4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboPort);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_ComboBaud);
	DDX_Control(pDX, IDC_CHECK_OPEN, m_CheckOpen);
	DDX_Control(pDX, IDC_EDIT_RECV, m_EditRecv);
	DDX_Control(pDX, IDC_EDIT_SEND, m_EditSend);
	DDX_Control(pDX, IDC_EDIT_TAR_POS_1, m_editTarPos1);
	DDX_Control(pDX, IDC_EDIT_CUR_POS_1, m_editCurPos1);
	DDX_Control(pDX, IDC_EDIT_TAR_POS_2, m_editTarPos2);
	DDX_Control(pDX, IDC_EDIT_CUR_POS_2, m_editCurPos2);
	DDX_Control(pDX, IDC_EDIT_TAR_VEL, m_editTarVel);
	DDX_Control(pDX, IDC_EDIT_CUR_VEL, m_editCurVel);
	DDX_Control(pDX, IDC_EDIT_TAR_TORQ, m_editTarTorq);
	DDX_Control(pDX, IDC_EDIT_CUR_TORQ, m_editCurTorq);
	DDX_Control(pDX, IDC_EDIT_TAR_X, m_editTarX);
	DDX_Control(pDX, IDC_EDIT_CUR_X, m_editCurX);
	DDX_Control(pDX, IDC_EDIT_TAR_Y, m_editTarY);
	DDX_Control(pDX, IDC_EDIT_CUR_Y, m_editCurY);
	DDX_Control(pDX, IDC_EDIT_TAR_Z, m_editTarZ);
	DDX_Control(pDX, IDC_EDIT_CUR_Z, m_editCurZ);
}

BEGIN_MESSAGE_MAP(CRobotExp_4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COMBO_PORT, &CRobotExp_4Dlg::OnCbnDropdownComboPort)
	ON_BN_CLICKED(IDC_CHECK_OPEN, &CRobotExp_4Dlg::OnBnClickedCheckOpen)
	ON_BN_CLICKED(IDC_BTN_SEND, &CRobotExp_4Dlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CRobotExp_4Dlg::OnBnClickedBtnClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CRobotExp_4Dlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CRobotExp_4Dlg::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD, &CRobotExp_4Dlg::OnBnClickedButtonBackward)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_GRAPH, &CRobotExp_4Dlg::OnBnClickedButtonGraph)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CRobotExp_4Dlg::OnBnClickedButtonSet)
	END_MESSAGE_MAP()


// CRobotExp_4Dlg �޽��� ó����

BOOL CRobotExp_4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetTimer(1001, 33, NULL);
	// SetTimer(1, 100, NULL);

	_commWorker.SetPeriod(0.01);
	_commWorker.SetWork(CreateWork<CCommWork>("Comm1Work"));

	m_editTarPos1.SetWindowTextA("0");
	m_editTarPos2.SetWindowTextA("0");
	m_editTarVel.SetWindowTextA("10");
	m_editTarTorq.SetWindowTextA("0.1");
	m_editTarX.SetWindowTextA("0.0");
	m_editTarY.SetWindowTextA("0.0");
	m_editTarZ.SetWindowTextA("0.0");

	m_pGraphDlg = new CGraphDlg;
	m_pGraphDlg->Create(IDD_GRAPH_DIALOG);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CRobotExp_4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CRobotExp_4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CRobotExp_4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRobotExp_4Dlg::SolveForwardKinematics(double dAngle, double dAngle2, double* pdPos)
{
	double l1 = 1.0;
	double l2 = 0.5;

	pdPos[0] = l1 * cos(dAngle) + l2*cos(dAngle + dAngle2);
	pdPos[1] = l1 * sin(dAngle) + l2*sin(dAngle + dAngle2);
	pdPos[2] = 0;
}


void CRobotExp_4Dlg::SolveInverseKinematics(double dX, double dY, double dZ, double* pdAngle)
{
	const double l1 = 1.0;      // link1�� ����
	const double l2 = 0.5;      // link2�� ����

	double c2 = (dX*dX + dY * dY - (l1*l1 + l2 * l2)) / (2 * l1*l2);
	double s2 = sqrt(1 - c2 * c2);
	double c1 = ((l1 + l2 * c2)*dX + (l2*s2)*dY) / (pow(l1 + l2 * c2, 2) + pow(l2*s2, 2));
	double s1 = (-(l2*s2*dX) + (l1 + l2 * c2)*dY) / (pow(l1 + l2 * c2, 2) + pow(l2*s2, 2));
	pdAngle[0] = atan2(s1, c1);

	pdAngle[1] = atan2(s2, c2);
}

void CRobotExp_4Dlg::OnCbnDropdownComboPort()
{
	CDeviceListReader reader;
	std::vector<std::string> list;

	// Combo Box �ʱ�ȭ
	m_ComboPort.ResetContent();

	reader.UpdateDeviceList("SERIALCOMM");
	reader.GetDeviceList(list);

	for (int i = 0; i < list.size(); i++) {
		m_ComboPort.AddString(list[i].c_str());
	}
}


void CRobotExp_4Dlg::OnBnClickedCheckOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_CheckOpen.GetCheck()) {
		CString port, baud;
		m_ComboPort.GetLBText(m_ComboPort.GetCurSel(), port);
		m_ComboBaud.GetLBText(m_ComboBaud.GetCurSel(), baud);
		int nTmp = atoi(baud.GetBuffer());

		ControlData_t motor_data;

		// Open�ÿ� ���Ϳ� �ʱ� ���� �����Ͽ� Init�� ������ �ʾƵ� ���ߵ��� ó���� //
		GET_SYSTEM_MEMORY("Comm1Work_Controller_Target", motor_data);

		motor_data.position = 0.;
		motor_data.velocity = 10 * DEG2RAD;
		motor_data.current = 0.1 / 0.0683;

		SET_SYSTEM_MEMORY("Comm1Work_Controller_Target", motor_data);
		////////////////////////

		if (((CCommWork*)_commWorker.GetWork())->OpenPort(port.GetBuffer(), nTmp)) {
			_commWorker.StartWork();
			m_CheckOpen.SetWindowTextA("Close");
		}
		else {
			AfxMessageBox("Can't open port");
			m_CheckOpen.SetCheck(false);
		}
	}
	else {
		_commWorker.StopWork();
		((CCommWork*)_commWorker.GetWork())->ClosePort();
		m_CheckOpen.SetWindowText("Open");
	}
	
}


void CRobotExp_4Dlg::OnBnClickedBtnSend()
{
	
}


void CRobotExp_4Dlg::OnBnClickedBtnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_EditRecv.SetWindowText("");
}


void CRobotExp_4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	ControlData_t motor_data;
	DataType_t ode_data;

	GET_SYSTEM_MEMORY("JointData", ode_data);
	GET_SYSTEM_MEMORY("Comm1Work_Controller_Current", motor_data);

	CString str;

	// ODE
	str.Format("%.4f", ode_data.Q_cur[2] * RAD2DEG);
	m_editCurPos2.SetWindowText(str);
	
	// Motor
	motor_data.position = fmod(motor_data.position, 360.0 * DEG2RAD);

	str.Format("%.4f", motor_data.position * RAD2DEG);
	CurPos = motor_data.position * RAD2DEG;
	m_editCurPos1.SetWindowText(str);
		

	str.Format("%.4f", motor_data.velocity * RAD2DEG);
	m_editCurVel.SetWindowText(str);
	CurVelo = motor_data.velocity  * RAD2DEG;

	str.Format("%.4f", motor_data.current * 0.0683);
	CurTorq = motor_data.current * 0.0683;
	m_editCurTorq.SetWindowText(str);

	// Forward Kinematics
	double Pcur[3] = { 0, };
	SolveForwardKinematics(ode_data.Q_cur[1], ode_data.Q_cur[2], Pcur);

	str.Format("%.4f", Pcur[0]);
	m_editCurX.SetWindowText(str);

	str.Format("%.4f", Pcur[1]);
	m_editCurY.SetWindowText(str);

	str.Format("%.4f", Pcur[2]);
	m_editCurZ.SetWindowText(str);

	CDialogEx::OnTimer(nIDEvent);
}


void CRobotExp_4Dlg::OnBnClickedButtonInit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_editTarX.SetWindowTextA("0");
	m_editTarY.SetWindowTextA("0");
	m_editTarZ.SetWindowTextA("0");

	m_editTarPos1.SetWindowTextA("0");
	m_editTarPos2.SetWindowTextA("0");

	m_editTarVel.SetWindowTextA("10");
	m_editTarTorq.SetWindowTextA("0.1");
	

	ControlData_t motor_data;
	DataType_t ode_data;

	GET_SYSTEM_MEMORY("JointData", ode_data);

	ode_data.Q_tar[0] = ode_data.Q_tar[1] =  ode_data.Q_tar[2] = 0.;
	SET_SYSTEM_MEMORY("JointData", ode_data);

	motor_data.position = 0.;
	motor_data.velocity = 10 * DEG2RAD;
	motor_data.current = 0.1 / 0.0683;
	SET_SYSTEM_MEMORY("Comm1Work_Controller_Target", motor_data);

}


void CRobotExp_4Dlg::OnBnClickedButtonForward()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	char cTmp[10];
	double dTmp[2];
	m_editTarPos1.GetWindowTextA(cTmp, 10);
	dTmp[0] = atof(cTmp);
	m_editTarPos2.GetWindowTextA(cTmp, 10);
	dTmp[1] = atof(cTmp);

	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);

	jointData.Q_tar[1] = dTmp[0];
	jointData.Q_tar[2] = dTmp[1];

	jointData.Q_tar[1] = fmod(jointData.Q_tar[1], 360.0);
	jointData.Q_tar[2] = fmod(jointData.Q_tar[2], 360.0);

	if (jointData.Q_tar[1] >= 180.0) jointData.Q_tar[1] -= 360.0;
	if (jointData.Q_tar[1] <= -180.0) jointData.Q_tar[1] += 360.0;

	if (jointData.Q_tar[2] >= 180.0) jointData.Q_tar[2] -= 360.0;
	if (jointData.Q_tar[2] <= -180.0) jointData.Q_tar[2] += 360.0;

	SET_SYSTEM_MEMORY("JointData", jointData);

	double dPos[3] = { 0, 0, 0 };

	SolveForwardKinematics(dTmp[0] * DEG2RAD, dTmp[1] * DEG2RAD, dPos);

	char pszTmp[512];

	sprintf_s(pszTmp, "%.2lf", dPos[0]);
	m_editTarX.SetWindowTextA(pszTmp);
	sprintf_s(pszTmp, "%.2lf", dPos[1]);
	m_editTarY.SetWindowTextA(pszTmp);
	sprintf_s(pszTmp, "%.2lf", dPos[2]);
	m_editTarZ.SetWindowTextA(pszTmp);
}


void CRobotExp_4Dlg::OnBnClickedButtonBackward()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char cTmp[10];
	double dTmp[3];
	m_editTarX.GetWindowTextA(cTmp, 10);
	dTmp[0] = atof(cTmp);
	m_editTarY.GetWindowTextA(cTmp, 10);
	dTmp[1] = atof(cTmp);
	m_editTarZ.GetWindowTextA(cTmp, 10);
	dTmp[2] = atof(cTmp);

	double dAngle[2] = { 0,0 };
	SolveInverseKinematics(dTmp[0], dTmp[1], dTmp[2], dAngle);

	char pszTmp[512];
	sprintf_s(pszTmp, "%.2lf", dAngle[0] * RAD2DEG);		// 
	m_editTarPos1.SetWindowTextA(pszTmp);
	sprintf_s(pszTmp, "%.2lf", dAngle[1] * RAD2DEG);		//
	m_editTarPos2.SetWindowTextA(pszTmp);

	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);

	jointData.Q_tar[1] = dAngle[0] * RAD2DEG;
	jointData.Q_tar[2] = dAngle[1] * RAD2DEG;

	jointData.Q_tar[1] = fmod(jointData.Q_tar[1], 360.0);
	jointData.Q_tar[2] = fmod(jointData.Q_tar[2], 360.0);

	if (jointData.Q_tar[1] >= 180.0) jointData.Q_tar[1] -= 360.0;
	if (jointData.Q_tar[1] <= -180.0) jointData.Q_tar[1] += 360.0;

	if (jointData.Q_tar[2] >= 180.0) jointData.Q_tar[2] -= 360.0;
	if (jointData.Q_tar[2] <= -180.0) jointData.Q_tar[2] += 360.0;

	SET_SYSTEM_MEMORY("JointData", jointData);
}


void CRobotExp_4Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pGraphDlg;

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CRobotExp_4Dlg::OnBnClickedButtonGraph()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bCheck = m_pGraphDlg->IsWindowVisible();
	if (bCheck) m_pGraphDlg->ShowWindow(SW_HIDE);
	else m_pGraphDlg->ShowWindow(SW_SHOW);
}


void CRobotExp_4Dlg::OnBnClickedButtonSet()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ControlData_t motor_data;
	DataType_t ode_data;

	GET_SYSTEM_MEMORY("JointData", ode_data);
	

	CString str;
	m_editTarPos1.GetWindowText(str);
	ode_data.Q_tar[1] = atof(str.GetBuffer());

	m_editTarPos2.GetWindowText(str);
	ode_data.Q_tar[2] = atof(str.GetBuffer());

	m_editTarPos1.GetWindowText(str);
	motor_data.position = (double)(atof(str.GetBuffer()) * DEG2RAD);

	m_editTarVel.GetWindowText(str);
	motor_data.velocity = (double)(atof(str.GetBuffer()) * DEG2RAD);
	TarVelo = atof(str.GetBuffer());

	m_editTarTorq.GetWindowText(str);
	motor_data.current = atof(str.GetBuffer()) / 0.0683;
	TarTorq = atof(str.GetBuffer());

	ode_data.Q_tar[1] = fmod(ode_data.Q_tar[1], 360.0);
	ode_data.Q_tar[2] = fmod(ode_data.Q_tar[2], 360.0);

	if (ode_data.Q_tar[1] >= 180.0) ode_data.Q_tar[1] -= 360.0;
	if (ode_data.Q_tar[1] <= -180.0) ode_data.Q_tar[1] += 360.0;

	if (ode_data.Q_tar[2] >= 180.0) ode_data.Q_tar[2] -= 360.0;
	if (ode_data.Q_tar[2] <= -180.0) ode_data.Q_tar[2] += 360.0;

	motor_data.position = fmod(motor_data.position * RAD2DEG, 360) * DEG2RAD;

	SET_SYSTEM_MEMORY("Comm1Work_Controller_Target", motor_data);
	SET_SYSTEM_MEMORY("JointData", ode_data);
}