
// Taurus7UTestProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Taurus7UTestProgram.h"
#include "Taurus7UTestProgramDlg.h"
#include "afxdialogex.h"

#include <vector>

#include "visa.h"
#include "visatype.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define WRITE_MEMORY_RX 0x00200000
#define WRITE_MEMORY_TX 0x00200004
#define WRITE_MEMORY_SIZE 0x00200008
#define WRITE_MEMORY_DATA 0x0020000C

#define READ_MEMORY_RX 0x00400000
#define READ_MEMORY_TX 0x00400004
#define READ_MEMORY_SIZE 0x00400008
#define READ_MEMORY_DATA 0x0040000C
int i = 0;
// CTaurus7UTestProgramDlg dialog

CTaurus7UTestProgramDlg::CTaurus7UTestProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTaurus7UTestProgramDlg::IDD, pParent)
	, m_CurrentDisplay(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaurus7UTestProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Write, m_Write);
	DDX_Control(pDX, IDC_WriteText, m_WriteString);
	DDX_Text(pDX, IDC_StatusText, m_CurrentDisplay);
	DDX_Control(pDX, IDC_StatusText, m_DisplayText);
}

BEGIN_MESSAGE_MAP(CTaurus7UTestProgramDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Config, &CTaurus7UTestProgramDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_Close, &CTaurus7UTestProgramDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_Write, &CTaurus7UTestProgramDlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_read, &CTaurus7UTestProgramDlg::OnBnClickedread)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CTaurus7UTestProgramDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_EXECMD, &CTaurus7UTestProgramDlg::OnBnClickedBtnExecmd)
	ON_BN_CLICKED(IDC_BUTTON2, &CTaurus7UTestProgramDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTaurus7UTestProgramDlg message handlers

BOOL CTaurus7UTestProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//m_WriteString.SetWindowTextW(_T("*IDN?\r\n"));
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTaurus7UTestProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTaurus7UTestProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTaurus7UTestProgramDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
	CString text;
	CStringA text_;
	try
	{
		ViStatus	status;
		//ViSession	defaultRM;
		ViFindList	fList;
		ViUInt32	retCount;					/* To hold number of resource */
		ViChar		rsrcName[VI_FIND_BUFLEN];	/* Serial resource name */
		//ViUInt16   iManf, iModel;
		std::vector<CString> vDevice;
		CString strInstrument;

		status = viOpenDefaultRM(&defaultRM);
		if (status == VI_SUCCESS)
		{
			status = viFindRsrc(defaultRM,"GPIB0::17::INSTR", &fList, &retCount, rsrcName);
			if (status == VI_SUCCESS)
			{
				int nList;

				status = viOpen(defaultRM, rsrcName, VI_NULL, VI_NULL, &instrSession);
				if (status < VI_SUCCESS)
				{
					CEdit *wEdit;
					wEdit = (CEdit*)GetDlgItem(IDC_StatusText);
					wEdit->SetWindowText(_T("viOpen fail.\r\n"));

				}
				else
				{
					
					ShowMsg(_T("Connected.\r\n"));
				
				}
			}
			else
			{
				ShowMsg(_T("viFindRsrc fail.\r\n"));
			}
		}
		
	}
	catch (...)
	{

	}

}


void CTaurus7UTestProgramDlg::OnBnClickedClose()
{
	//viClear(instrSession);
	viClose(defaultRM);
	//CString strCmd;
	//strCmd.Format(_T(":ROUT:FUNC ACON"));
	//WriteCmd(strCmd);
	//::Sleep(1000);
}

void CTaurus7UTestProgramDlg::OnBnClickedBtnClear()
{
	// TODO: Add your control notification handler code here

	CEdit *wEdit;
	wEdit = (CEdit*)GetDlgItem(IDC_StatusText);
	wEdit->SetWindowTextW(_T(""));
}

void CTaurus7UTestProgramDlg::ShowMsg(CString strMSg)
{
	int end = m_DisplayText.GetWindowTextLengthW();
	m_DisplayText.SetSel(end, end);
	CString strMsg;
	//if (end != 0)
	//	strMsg.Format(_T("\r\n%s"), strMSg);
	//else
		strMsg.Format(_T("%s"), strMSg);

	m_DisplayText.ReplaceSel(strMsg);
}

void CTaurus7UTestProgramDlg::OnBnClickedBtnExecmd()//Drict GPIB
{
	CString strVi;
	CString strRe;

	
	
	VisaWrite(_T("*IDN?"));
	OnBnClickedread();
	
	//VisaWrite(_T("*RST?"));
	
	VisaWrite(_T("FMT 21,0"));

	
	LARGE_INTEGER m_start, m_stop, m_dummy; //start time
	double m_freq;
	double totlaTime;
	QueryPerformanceFrequency(&m_dummy);
	m_freq = (double)m_dummy.QuadPart;
	QueryPerformanceCounter(&m_start);

	for (int i = 2; i <= 4; i++)
	{
		strVi.Format(_T("RI%d,0"),i);
		VisaWrite(strVi);
		//OnBnClickedread();
		
	}
	VisaWrite(_T("ERRX? 0"));
	OnBnClickedread();
	
	VisaWrite(_T("AIT1,0"));
	VisaWrite(_T("CN2"));
	VisaWrite(_T("DV2,0,0,0.1"));	 // D
		
	VisaWrite(_T("CN3"));
	VisaWrite(_T("DV3,0,2.5,0.1"));// G

	VisaWrite(_T("CN4"));
	VisaWrite(_T("DV4,0,0,0.1"));// S

	VisaWrite(_T("*OPC?"));
	OnBnClickedread();
	//VisaRead(strRe);
	
	VisaWrite(_T("CMM2,1"));
	VisaWrite(_T("MM1,2"));
	
	//VisaRead(strRe);
	

	
	
	int i = 0;
	double forceV = 0;
	
	for (i = 0; i <= 24; i++)
	{
		strVi.Format(_T("DV2,0,%f,0.1"), forceV);
		VisaWrite(strVi);
		VisaWrite(_T("XE"));
		forceV = forceV + 0.1;
		OnBnClickedread();
		
		//VisaRead(strRe);
		
	}

	QueryPerformanceCounter(&m_stop);
		
	VisaWrite(_T("IN2,3,4"));
	VisaWrite(_T("CL2,3,4"));
	VisaWrite(_T("ERRX? 0"));
	OnBnClickedread();
	//VisaRead(strRe);
	



	/*time_t curtime;
	time(&curtime);

	MessageBox(NULL, (CString)ctime(&curtime), 1);*/

	

}

void CTaurus7UTestProgramDlg::WriteCmd(CString strCmd)
{
	CStringA strCmd_;
	strCmd_ = strCmd;
	ViStatus vistatus_ = 0L;
	ViUInt32 nRetCnt = 0;
	vistatus_ = viWrite(instrSession, (ViPBuf)strCmd_.GetString(), (ViUInt32)strCmd_.GetLength(), &nRetCnt);
	ShowMsg(strCmd);
}



void CTaurus7UTestProgramDlg::OnBnClickedWrite()
{
	// clear the received buffer
	CString strCmd;
	CStringA strCmd_;
	ViStatus vistatus_ = 0L;
	ViUInt32 nRetCnt = 0;

	m_WriteString.GetWindowTextW(strCmd);
	strCmd.Append(_T("\r\n"));
	strCmd_ = strCmd;
	vistatus_ = viWrite(instrSession, (ViPBuf)strCmd_.GetBuffer(), (ViUInt32)strCmd_.GetLength(), &nRetCnt);
	//ShowMsg(strCmd);
}


void CTaurus7UTestProgramDlg::OnBnClickedread()
{
	CString strData;

	CEdit *wEdit;
	wEdit = (CEdit*)GetDlgItem(IDC_StatusText);
	//wEdit->SetWindowTextW(strData);

	char *cstr = new char[4096];

	ViStatus vistatus_ = 0L;
	ViUInt32 nRetCnt = 0;


	//vistatus_ = viRead(m_objSession, (unsigned char *)str, 400050, &nRetCnt);
	vistatus_ = viRead(instrSession, (ViPBuf)cstr, 4096, &nRetCnt);

	CString cstr_temp;
	cstr_temp = cstr;
	strData = cstr_temp.Left(nRetCnt);
	delete[] cstr;

	ShowMsg(strData);

	::Sleep(60);
}

void CTaurus7UTestProgramDlg::VisaWrite(CString srtVi)
{
	CStringA strVi_;
	ViStatus vistatus_ = 0L;
	ViUInt32 nRetCnt = 0;
	strVi_ = srtVi;
	
	vistatus_ = viWrite(instrSession, (ViPBuf)strVi_.GetBuffer(), (ViUInt32)strVi_.GetLength(), &nRetCnt);
	
}



void CTaurus7UTestProgramDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}
