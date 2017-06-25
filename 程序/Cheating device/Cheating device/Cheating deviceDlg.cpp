
// Cheating deviceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Cheating device.h"
#include "Cheating deviceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCheatingdeviceDlg 对话框



CCheatingdeviceDlg::CCheatingdeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHEATINGDEVICE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheatingdeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CCheatingdeviceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CCheatingdeviceDlg 消息处理程序

BOOL CCheatingdeviceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);

	m_list.SetExtendedStyle(
		LVS_EX_FLATSB               //扁平风格滚动条
		| LVS_EX_FULLROWSELECT      //允许整行选中
		| LVS_EX_HEADERDRAGDROP     //允许标题拖曳
		| LVS_EX_ONECLICKACTIVATE   //高亮显示
		| LVS_EX_GRIDLINES          //画出网格线
		//| LVS_EX_CHECKBOXES         //设置成扩展控件
	);

	m_list.InsertColumn(0, _T("Id"), LVCFMT_LEFT, rect.Width()*0.05);
	m_list.InsertColumn(1, _T("Question"), LVCFMT_LEFT, rect.Width()*0.13);
	m_list.InsertColumn(2, _T("A"), LVCFMT_CENTER, rect.Width()*0.14);
	m_list.InsertColumn(3, _T("B"), LVCFMT_CENTER, rect.Width()*0.14);
	m_list.InsertColumn(4, _T("C"), LVCFMT_CENTER, rect.Width()*0.14);
	m_list.InsertColumn(5, _T("D"), LVCFMT_CENTER, rect.Width()*0.14);
	m_list.InsertColumn(6, _T("E"), LVCFMT_CENTER, rect.Width()*0.14);
	m_list.InsertColumn(7, _T("Answer"), LVCFMT_RIGHT, rect.Width()*0.12);
	for (int i = 0; i < 10; ++i) {
		int nRow = m_list.InsertItem(0, NULL);// 插入行
		m_list.SetItemText(0, 0, _T("1"));// 设置其它列数据
		m_list.SetItemText(0, 1, _T("问题"));
		m_list.SetItemText(0, 2, _T("A"));
		m_list.SetItemText(0, 3, _T("B"));
		m_list.SetItemText(0, 4, _T("C"));
		m_list.SetItemText(0, 5, _T("D"));
		m_list.SetItemText(0, 6, _T("E"));
		m_list.SetItemText(0, 7, _T("回答回答回答回答回答回答"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCheatingdeviceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCheatingdeviceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCheatingdeviceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCheatingdeviceDlg::OnOK()
{
}

BOOL CCheatingdeviceDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE) {
		pMsg->wParam = VK_RETURN;                  //将ESC键的消息替换为回车键的消息，这样，按ESC的时候
												   //也会去调用OnOK函数，而OnOK什么也不做，这样ESC也被屏蔽
	}
	return CDialog::PreTranslateMessage(pMsg);
}

