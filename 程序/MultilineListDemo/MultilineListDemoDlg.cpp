// MultilineListDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultilineListDemo.h"
#include "MultilineListDemoDlg.h"
#include ".\multilinelistdemodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMultilineListDemoDlg dialog



CMultilineListDemoDlg::CMultilineListDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultilineListDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_initialized = FALSE;
}

void CMultilineListDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEMS, m_items);
}

BEGIN_MESSAGE_MAP(CMultilineListDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMultilineListDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMultilineListDemoDlg message handlers

BOOL CMultilineListDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//multiline list set
	CRect wr;
	GetWindowRect(wr);
	CRect cr;
	m_items.GetWindowRect(cr);
	m_edgeDelta.cx = wr.right - cr.right;
	m_edgeDelta.cy = wr.bottom - cr.bottom;
	m_initialized = TRUE;

	//single radio group set
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(true);

	//list show set
	m_items.SetSize(8, 0);
	m_items.SetColHeading(0, _T("ID"));
	m_items.SetColHeading(1, _T("QUESTIONS"));
	m_items.SetColHeading(2, _T("OPTION A"));
	m_items.SetColHeading(3, _T("OPTION B"));
	m_items.SetColHeading(4, _T("OPTION C"));
	m_items.SetColHeading(5, _T("OPTION D"));
	m_items.SetColHeading(6, _T("OPTION E"));
	m_items.SetColHeading(7, _T("ANSWERS"));

	//list width set
	m_items.SetColWidth(0, 35);
	m_items.SetColWidth(1, 285);
	m_items.SetColWidth(7, 40);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultilineListDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultilineListDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultilineListDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMultilineListDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (!m_initialized)
		return;

	CRect wr;
	GetWindowRect(wr);
	CRect cr;
	m_items.GetWindowRect(cr);

	cr.right = wr.right - m_edgeDelta.cx;
	cr.bottom = wr.bottom - m_edgeDelta.cy;

	ScreenToClient(cr);
	m_items.MoveWindow(cr);
	m_items.Invalidate(FALSE);
}


BOOL CMultilineListDemoDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((HIWORD(wParam) == LBN_SELCHANGE) &&
		(LOWORD(wParam) == IDC_ITEMS))
	{
		int selRow = m_items.GetSelRow();

		if (selRow < 0)
		{
			SetWindowText(_T("Title finder"));
		}
		else
		{
			CString s;
			s.Format(_T("Title finder  (you have selected %s)"), m_items.GetCellText(0, selRow));
			SetWindowText(s);
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CMultilineListDemoDlg::InitDataBase()
{
	if (((CButton*)GetDlgItem(IDC_RADIO5))->GetCheck() == 1) {                                          //local database
		//waiting...



	}
	else {
		if ((questionDataBase.Open(_T("QuestionDataBase"), false, false, _T("ODBC;UID=sa;pwd=123456"), true)) != 0) {    //sucsess
			AfxMessageBox("DataBase linked success !", MB_OK | MB_ICONINFORMATION);
		}
		else {
			AfxMessageBox("DataBase linked fail !", MB_OK | MB_ICONSTOP);
			exit(-1);
			return false;
		}
	}
	return true;
}

void CMultilineListDemoDlg::OnBnClickedButton1()               //searching
{
	int numRows;
	CString strTemp;

	InitDataBase();

	//find choice table
	int flagID = IDC_RADIO1;
	for (int i = 1; i < 4; ++i) {
		if (((CButton*)GetDlgItem(IDC_RADIO1 + i))->GetCheck() == 1) {
			flagID = IDC_RADIO1 + i;
		}
	}

	switch (flagID)
	{
	case IDC_RADIO1:
	{
		m_judgeAnswer = new JudgeQuestion(&questionDataBase);
		m_judgeAnswer->Open(CRecordset::forwardOnly, _T("select count(*) from Judge"));
		m_judgeAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_judgeAnswer;
		m_judgeAnswer = new JudgeQuestion(&questionDataBase);
		m_judgeAnswer->Open(CRecordset::forwardOnly, _T("select * from Judge"));
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO1, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	case IDC_RADIO2:
	{
		m_oneAnswer = new OnechoiceQuestion(&questionDataBase);
		m_oneAnswer->Open(CRecordset::forwardOnly, _T("select count(*) from Onechoice"));
		m_oneAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_oneAnswer;
		m_oneAnswer = new OnechoiceQuestion(&questionDataBase);
		m_oneAnswer->Open(CRecordset::forwardOnly, _T("select * from Onechoice"));
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO2, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	case IDC_RADIO3:
	{
		m_moreAnswer = new MorechoiceQuestion(&questionDataBase);
		m_moreAnswer->Open(CRecordset::forwardOnly, _T("select count(*) from Morechoice"));
		m_moreAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_moreAnswer;
		m_moreAnswer = new MorechoiceQuestion(&questionDataBase);
		m_moreAnswer->Open(CRecordset::forwardOnly, _T("select * from Morechoice"));
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO3, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	case IDC_RADIO4:
	{
		m_shortAnswer = new ShortQuestion(&questionDataBase);
		m_shortAnswer->Open(CRecordset::forwardOnly, _T("select count(*) from [Short]"));
		m_shortAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_shortAnswer;
		m_shortAnswer = new ShortQuestion(&questionDataBase);
		m_shortAnswer->Open(CRecordset::forwardOnly, _T("select * from [Short]"));
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO4, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	default:break;
	}
	//close database
	questionDataBase.Close();
}

void CMultilineListDemoDlg::PopulateItemList(int flagID, int numRows)
{
	CString str;
	m_items.SetSize(numCols, numRows);

	if(flagID != IDC_RADIO4){
		m_items.SetColWidth(0, 35);
		m_items.SetColWidth(1, 285);
		for(int i = 2; i < 7; ++i){
			m_items.SetColWidth(i, 100);
		}
		m_items.SetColWidth(7, 40);
	}else{
		m_items.SetColWidth(0, 35);
		m_items.SetColWidth(1, 300);
		for(int i = 2; i < 7; ++i){
			m_items.SetColWidth(i, 0);
		}
		m_items.SetColWidth(7, 525);
	}
	switch(flagID)
	{
	case IDC_RADIO1:
	{
		short nFields = m_judgeAnswer->GetODBCFieldCount();
		for (int rows = 0; rows <= numRows && !(m_judgeAnswer->IsEOF()); ++rows) {
			for (short index = 0; index < nFields; ++index) {
				m_judgeAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, rows, str);
			}
			m_judgeAnswer->MoveNext();
		}
	}
	break;
	case IDC_RADIO2:
	{
		short nFields = m_oneAnswer->GetODBCFieldCount();
		for (int rows = 0; rows <= numRows && !(m_oneAnswer->IsEOF()); ++rows) {
			for (short index = 0; index < nFields; ++index) {
				m_oneAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, rows, str);
			}
			m_oneAnswer->MoveNext();
		}
	}
	break;
	case IDC_RADIO3:
	{
		short nFields = m_moreAnswer->GetODBCFieldCount();
		for (int rows = 0; rows <= numRows && !(m_moreAnswer->IsEOF()); ++rows) {
			for (short index = 0; index < nFields; ++index) {
				m_moreAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, rows, str);
			}
			m_moreAnswer->MoveNext();
		}
	}
	break;
	case IDC_RADIO4:
	{
		short nFields = m_shortAnswer->GetODBCFieldCount();
		for (int rows = 0; rows <= numRows && !(m_shortAnswer->IsEOF()); ++rows) {
			for (short index = 0; index < nFields; ++index) {
				m_shortAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, rows, str);
			}
			m_shortAnswer->MoveNext();
		}
	}
	break;
	default:break;
	}
}