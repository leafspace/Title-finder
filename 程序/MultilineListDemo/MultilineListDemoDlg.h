// MultilineListDemoDlg.h : header file
//

#pragma once
#include "multilinelist.h"
#include "DataBaseStruct.h"
#include "afxwin.h"


// CMultilineListDemoDlg dialog
class CMultilineListDemoDlg : public CDialog
{
	// Construction
public:
	CMultilineListDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MULTILINELISTDEMO_DIALOG };

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
	BOOL m_initialized;
	CSize m_edgeDelta;
	CMultilineList m_items;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
private:
	static const int numCols = 8;

	CDatabase questionDataBase;

	OnechoiceQuestion *m_oneAnswer;
	MorechoiceQuestion *m_moreAnswer;
	JudgeQuestion *m_judgeAnswer;
	ShortQuestion *m_shortAnswer;

	afx_msg void OnBnClickedButton1();
	void PopulateItemList(int, int);
	BOOL InitDataBase();
};
