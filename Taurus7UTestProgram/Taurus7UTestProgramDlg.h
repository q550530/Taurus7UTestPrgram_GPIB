
// Taurus7UTestProgramDlg.h : header file
//

#define NIVISA_PXI
#pragma once
#include "NI Headers_vc120\visa.h"
#include "NI Headers_vc120\visatype.h"
#include "afxwin.h"

// CTaurus7UTestProgramDlg dialog
class CTaurus7UTestProgramDlg : public CDialogEx
{
// Construction
public:
	CTaurus7UTestProgramDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TAURUS7UTESTPROGRAM_DIALOG };
	CEdit m_Write;
	CEdit m_WriteString;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//std::auto_ptr<ViSession> m_instr;
	//std::auto_ptr<ViSession> m_instr1;
	ViSession defaultRM;
	
public:
	ViSession	instrSession;
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedread();
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedBtnExecmd();
	afx_msg void OnBnClickedBtnClear();

	CString m_CurrentDisplay;
	CEdit m_DisplayText;


	/*void WriteGpibVisa(CString strcmd);
	void ReadGpibVisa(CString &strdata);
	void writeGpib(ViSession *session, const CString strCmd);
	void readGpib(ViSession *session, CString &strData);
	void Clear(ViSession *session);
	void SetTimeout(ViSession *session);*/
	
	void PCIeInterruptDetect();
	void ShowMsg(CString strMSg);
	void WriteCmd(CString strCmd);
	void VisaWrite(CString strVi);
	void VisaRead(CString &strRe);
		
	afx_msg void OnBnClickedButton2();
};
