
// MFCApplication1Dlg.h : header file
//

#pragma once
#include"Core.h"

#define WM_RANDOM_STEP (WM_APP + 1)
#define WM_RANDOM_FINISH (WM_APP + 2)


#define MINSIZE 1
#define MAXSIZE 50

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
private:
	std::unique_ptr<Core> core;

	bool isDragging = false;
	int draggingPointIndex = -1;

	int circleSize;
	int thickness;

	bool isRandomRunning = false;
	UINT randomRunId = 0;
private:
	bool CheckSize();

	// Thread
	static UINT RandomThread(LPVOID parameter);
	afx_msg LRESULT OnRandomStep(WPARAM, LPARAM);
	afx_msg LRESULT OnRandomFinish(WPARAM, LPARAM);
	
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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
