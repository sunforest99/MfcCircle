
// MFCApplication1Dlg.h : header file
//

#pragma once
#include"Core.h"

#define MINSIZE 1
#define MAXSIZE 50

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
private:
	std::unique_ptr<Core> core;

private:
	bool CheckSize();
	
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor
	~CMFCApplication1Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedReset();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRandombtn();
};
