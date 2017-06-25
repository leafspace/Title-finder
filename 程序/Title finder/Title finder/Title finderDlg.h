// Title finderDlg.h : 头文件
//

#pragma once
#include "multilinelist.h"
#include "DataBaseStruct.h"
#include "afxwin.h"
#include <vector>
using namespace std;

// CTitlefinderDlg 对话框
class CTitlefinderDlg : public CDialog
{
	// 构造
public:
	CTitlefinderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TITLEFINDER_DIALOG };

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
public:
	BOOL m_initialized;
	CSize m_edgeDelta;
	CMultilineList m_items;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
private:
	static const int numCols = 8;

	CString selectString[8];
	CString keyWords;

	CDatabase questionDataBase;

	OnechoiceQuestion *m_oneAnswer;
	MorechoiceQuestion *m_moreAnswer;
	JudgeQuestion *m_judgeAnswer;
	ShortQuestion *m_shortAnswer;

	afx_msg void OnBnClickedButton1();
	BOOL InitDataBase();
	void DirectSearch(int);
	void KeywordSearch(int);
	void PopulateItemList(int, int);
	void PopulateItemList(int[][2], int, int);
};

class keywordIndex
{
public:
	CString keyword;
	vector<int> keyID;
	keywordIndex(CString ke, vector<int> kI) {
		keyword = ke;
		keyID = kI;
	}
};
