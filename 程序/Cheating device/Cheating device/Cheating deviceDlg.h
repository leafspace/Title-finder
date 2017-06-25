
// Cheating deviceDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

// CCheatingdeviceDlg 对话框
class CCheatingdeviceDlg : public CDialogEx
{
// 构造
public:
	CCheatingdeviceDlg(CWnd* pParent = NULL);	// 标准构造函数
	void OnOK();
	BOOL PreTranslateMessage(MSG* pMsg);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHEATINGDEVICE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_list;
};

