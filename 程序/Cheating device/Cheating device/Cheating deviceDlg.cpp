
// Cheating deviceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cheating device.h"
#include "Cheating deviceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCheatingdeviceDlg �Ի���



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


// CCheatingdeviceDlg ��Ϣ�������

BOOL CCheatingdeviceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
	GetDlgItem(IDC_LIST1)->GetWindowRect(&rect);

	m_list.SetExtendedStyle(
		LVS_EX_FLATSB               //��ƽ��������
		| LVS_EX_FULLROWSELECT      //��������ѡ��
		| LVS_EX_HEADERDRAGDROP     //���������ҷ
		| LVS_EX_ONECLICKACTIVATE   //������ʾ
		| LVS_EX_GRIDLINES          //����������
		//| LVS_EX_CHECKBOXES         //���ó���չ�ؼ�
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
		int nRow = m_list.InsertItem(0, NULL);// ������
		m_list.SetItemText(0, 0, _T("1"));// ��������������
		m_list.SetItemText(0, 1, _T("����"));
		m_list.SetItemText(0, 2, _T("A"));
		m_list.SetItemText(0, 3, _T("B"));
		m_list.SetItemText(0, 4, _T("C"));
		m_list.SetItemText(0, 5, _T("D"));
		m_list.SetItemText(0, 6, _T("E"));
		m_list.SetItemText(0, 7, _T("�ش�ش�ش�ش�ش�ش�"));
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCheatingdeviceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		pMsg->wParam = VK_RETURN;                  //��ESC������Ϣ�滻Ϊ�س�������Ϣ����������ESC��ʱ��
												   //Ҳ��ȥ����OnOK��������OnOKʲôҲ����������ESCҲ������
	}
	return CDialog::PreTranslateMessage(pMsg);
}

