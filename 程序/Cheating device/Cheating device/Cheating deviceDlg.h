
// Cheating deviceDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

// CCheatingdeviceDlg �Ի���
class CCheatingdeviceDlg : public CDialogEx
{
// ����
public:
	CCheatingdeviceDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void OnOK();
	BOOL PreTranslateMessage(MSG* pMsg);
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHEATINGDEVICE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_list;
};

