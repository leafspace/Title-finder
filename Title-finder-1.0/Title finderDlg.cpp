// Title finderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Title finder.h"
#include "Title finderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTitlefinderDlg 对话框




CTitlefinderDlg::CTitlefinderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTitlefinderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_initialized = FALSE;
}

void CTitlefinderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEMS, m_items);
}

BEGIN_MESSAGE_MAP(CTitlefinderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CTitlefinderDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTitlefinderDlg 消息处理程序

BOOL CTitlefinderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

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
	((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(true);

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

	//select string set
	selectString[0] = "select count(*) from [Judge]";
	selectString[1] = "select * from [Judge]";
	selectString[2] = "select count(*) from [Onechoice]";
	selectString[3] = "select * from [Onechoice]";
	selectString[4] = "select count(*) from [Morechoice]";
	selectString[5] = "select * from [Morechoice]";
	selectString[6] = "select count(*) from [Short]";
	selectString[7] = "select * from [Short]";

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTitlefinderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTitlefinderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTitlefinderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTitlefinderDlg::OnSize(UINT nType, int cx, int cy)
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


BOOL CTitlefinderDlg::OnCommand(WPARAM wParam, LPARAM lParam)
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

BOOL CTitlefinderDlg::InitDataBase()
{
	if (((CButton*)GetDlgItem(IDC_RADIO5))->GetCheck() == 1) {                                          //local database
		//waiting...
		AfxMessageBox((CString)"对不起 还没开发", MB_OK | MB_ICONINFORMATION);
		PostQuitMessage(0);


	}
	else {
		if ((questionDataBase.Open(_T("QuestionDataBase"), false, false, _T("ODBC;UID=sa;pwd=123456"), true)) != 0) {    //sucsess
			AfxMessageBox((CString)"DataBase linked success !", MB_OK | MB_ICONINFORMATION);
		}
		else {
			AfxMessageBox((CString)"DataBase linked fail !", MB_OK | MB_ICONSTOP);
			exit(-1);
			return false;
		}
	}
	return true;
}

void CTitlefinderDlg::OnBnClickedButton1()               //searching
{
	InitDataBase();

	GetDlgItem(IDC_EDIT1)->GetWindowText(keyWords);

	//find choice table
	int flagID = IDC_RADIO1;
	for (int i = 1; i < 4; ++i) {
		if (((CButton*)GetDlgItem(IDC_RADIO1 + i))->GetCheck() == 1) {
			flagID = IDC_RADIO1 + i;
		}
	}

	if (((CButton*)GetDlgItem(IDC_RADIO7))->GetCheck() == 1) {
		DirectSearch(flagID);
	}
	else {
		KeywordSearch(flagID);
	}

	//close database
	questionDataBase.Close();
}

void CTitlefinderDlg::DirectSearch(int flagID)
{
	int numRows;
	CString strTemp;

	CString tempNumSelect;
	CString tempSelect;

	switch (flagID)
	{
	case IDC_RADIO1:
	{
		tempNumSelect = selectString[0];
		tempNumSelect += _T(" where Judge.Question like '%");
		tempNumSelect += keyWords + _T("%'");
		tempSelect = selectString[1];
		tempSelect += _T(" where Judge.Question like '%");
		tempSelect += keyWords + _T("%'");

		m_judgeAnswer = new JudgeQuestion(&questionDataBase);
		m_judgeAnswer->Open(CRecordset::forwardOnly, tempNumSelect);
		m_judgeAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_judgeAnswer;
		m_judgeAnswer = new JudgeQuestion(&questionDataBase);
		m_judgeAnswer->Open(CRecordset::forwardOnly, tempSelect);
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO1, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	case IDC_RADIO2:
	{
		tempNumSelect = selectString[2];
		tempNumSelect += _T(" where Onechoice.Question like '%");
		tempNumSelect += keyWords + _T("%'");
		tempSelect = selectString[3];
		tempSelect += _T(" where Onechoice.Question like '%");
		tempSelect += keyWords + _T("%'");

		m_oneAnswer = new OnechoiceQuestion(&questionDataBase);
		m_oneAnswer->Open(CRecordset::forwardOnly, tempNumSelect);
		m_oneAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_oneAnswer;
		m_oneAnswer = new OnechoiceQuestion(&questionDataBase);
		m_oneAnswer->Open(CRecordset::forwardOnly, tempSelect);
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO2, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	case IDC_RADIO3:
	{
		tempNumSelect = selectString[4];
		tempNumSelect += _T(" where Morechoice.Question like '%");
		tempNumSelect += keyWords + _T("%'");
		tempSelect = selectString[5];
		tempSelect += _T(" where Morechoice.Question like '%");
		tempSelect += keyWords + _T("%'");

		m_moreAnswer = new MorechoiceQuestion(&questionDataBase);
		m_moreAnswer->Open(CRecordset::forwardOnly, tempNumSelect);
		m_moreAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_moreAnswer;
		m_moreAnswer = new MorechoiceQuestion(&questionDataBase);
		m_moreAnswer->Open(CRecordset::forwardOnly, tempSelect);
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO3, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	case IDC_RADIO4:
	{
		tempNumSelect = selectString[6];
		tempNumSelect += _T(" where Short.Question like '%");
		tempNumSelect += keyWords + _T("%'");
		tempSelect = selectString[7];
		tempSelect += _T(" where Short.Question like '%");
		tempSelect += keyWords + _T("%'");

		m_shortAnswer = new ShortQuestion(&questionDataBase);
		m_shortAnswer->Open(CRecordset::forwardOnly, tempNumSelect);
		m_shortAnswer->GetFieldValue((short)0, strTemp);
		numRows = _ttoi(strTemp);
		delete m_shortAnswer;
		m_shortAnswer = new ShortQuestion(&questionDataBase);
		m_shortAnswer->Open(CRecordset::forwardOnly, tempSelect);
		SetWindowText(_T("Title finder   Please waiting a minute!"));
		PopulateItemList(IDC_RADIO4, numRows);
		SetWindowText(_T("Title finder"));
	}
	break;
	default:break;
	}
}

void CTitlefinderDlg::KeywordSearch(int flagID)
{
	vector<keywordIndex> keyword;
	CString tempStr;
	for (int i = 0, count = 0; i < keyWords.GetLength();) {
		while (true) {
			if (keyWords.GetAt(i + count) == ',' || keyWords.GetAt(i + count) == '，' || keyWords.GetAt(i + count) == ' ') {
				break;
			}
			++count;
			if ((i + count) == keyWords.GetLength()) {
				break;
			}
		}
		if (count == 0) {
			break;
		}
		{
			tempStr = keyWords.Mid(i, count);
			vector<int> keyID;
			CString tempSelect;
			CString str;
			switch (flagID)
			{
			case IDC_RADIO1:
				tempSelect = selectString[1];
				tempSelect += _T(" where Judge.Question like '%");
				tempSelect += tempStr + _T("%'");
				m_judgeAnswer = new JudgeQuestion(&questionDataBase);
				m_judgeAnswer->Open(CRecordset::forwardOnly, tempSelect);
				while (!(m_judgeAnswer->IsEOF())) {
					m_judgeAnswer->GetFieldValue((short)0, str);
					m_judgeAnswer->MoveNext();
					keyID.push_back(_ttoi(str));
				}
				break;
			case IDC_RADIO2:
				tempSelect = selectString[3];
				tempSelect += _T(" where Onechoice.Question like '%");
				tempSelect += tempStr + _T("%'");
				m_oneAnswer = new OnechoiceQuestion(&questionDataBase);
				m_oneAnswer->Open(CRecordset::forwardOnly, tempSelect);
				while (!(m_oneAnswer->IsEOF())) {
					m_oneAnswer->GetFieldValue((short)0, str);
					m_oneAnswer->MoveNext();
					keyID.push_back(_ttoi(str));
				}
				break;
			case IDC_RADIO3:
				tempSelect = selectString[5];
				tempSelect += _T(" where Morechoice.Question like '%");
				tempSelect += tempStr + _T("%'");
				m_moreAnswer = new MorechoiceQuestion(&questionDataBase);
				m_moreAnswer->Open(CRecordset::forwardOnly, tempSelect);
				while (!(m_moreAnswer->IsEOF())) {
					m_moreAnswer->GetFieldValue((short)0, str);
					m_moreAnswer->MoveNext();
					keyID.push_back(_ttoi(str));
				}
				break;
			case IDC_RADIO4:
				tempSelect = selectString[7];
				tempSelect += _T(" where Short.Question like '%");
				tempSelect += tempStr + _T("%'");
				m_shortAnswer = new ShortQuestion(&questionDataBase);
				m_shortAnswer->Open(CRecordset::forwardOnly, tempSelect);
				while (!(m_shortAnswer->IsEOF())) {
					m_shortAnswer->GetFieldValue((short)0, str);
					m_shortAnswer->MoveNext();
					keyID.push_back(_ttoi(str));
				}
				break;
			default:break;
			}
			keywordIndex temp(tempStr, keyID);
			keyword.push_back(temp);
		}
		i += count;
		++i;
		count = 0;
	}

	int IdList[100][2] = { 0 };
	int IdNum = 0;
	for (int i = 0; i < (int)keyword.size(); ++i) {
		keywordIndex temp = keyword[i];
		for (int j = 0; j < (int)temp.keyID.size(); ++j) {
			int tempKeyID = temp.keyID[j];
			int k;
			for (k = 0; k < IdNum; ++k) {
				if (IdList[k][0] == tempKeyID) {
					break;
				}
			}
			if (k == IdNum) {
				if (k == 100) {
					break;
				}
				IdList[IdNum][0] = tempKeyID;
				IdList[IdNum][1] = 1;
				IdNum++;
			}
			else {
				IdList[k][1]++;
			}
		}
	}

	int low = 0;
	int high = IdNum - 1;
	while (low < high) {
		for (int i = low; i < high; ++i)
			if (IdList[i][1] < IdList[i + 1][1]) {
				int temp = IdList[i][0];
				IdList[i][0] = IdList[i + 1][0];
				IdList[i + 1][0] = temp;

				temp = IdList[i][1];
				IdList[i][1] = IdList[i + 1][1];
				IdList[i + 1][1] = temp;
			}
		--high;
		for (int i = high; i > low; --i)
			if (IdList[i][1] > IdList[i - 1][1]) {
				int temp = IdList[i][0];
				IdList[i][0] = IdList[i - 1][0];
				IdList[i - 1][0] = temp;

				temp = IdList[i][1];
				IdList[i][1] = IdList[i - 1][1];
				IdList[i - 1][1] = temp;
			}
		++low;
	}
	PopulateItemList(IdList, flagID, IdNum);
}

void CTitlefinderDlg::PopulateItemList(int flagID, int numRows)
{
	CString str;

	//clear more data
	m_items.SetSize(numCols, 0);

	m_items.SetSize(numCols, numRows);

	if (flagID != IDC_RADIO4) {
		m_items.SetColWidth(0, 35);
		m_items.SetColWidth(1, 285);
		for (int i = 2; i < 7; ++i) {
			m_items.SetColWidth(i, 100);
		}
		m_items.SetColWidth(7, 40);
	}
	else {
		m_items.SetColWidth(0, 35);
		m_items.SetColWidth(1, 300);
		for (int i = 2; i < 7; ++i) {
			m_items.SetColWidth(i, 0);
		}
		m_items.SetColWidth(7, 525);
	}
	switch (flagID)
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

void CTitlefinderDlg::PopulateItemList(int IdList[][2], int flagID, int numRows)
{
	CString str;
	CString tempSelect;

	//clear more data
	m_items.SetSize(numCols, 0);

	m_items.SetSize(numCols, numRows);

	if (flagID != IDC_RADIO4) {
		m_items.SetColWidth(0, 35);
		m_items.SetColWidth(1, 285);
		for (int i = 2; i < 7; ++i) {
			m_items.SetColWidth(i, 100);
		}
		m_items.SetColWidth(7, 40);
	}
	else {
		m_items.SetColWidth(0, 35);
		m_items.SetColWidth(1, 300);
		for (int i = 2; i < 7; ++i) {
			m_items.SetColWidth(i, 0);
		}
		m_items.SetColWidth(7, 525);
	}

	switch (flagID)
	{
	case IDC_RADIO1:
	{
		for (int i = 0; i < numRows; ++i) {
			str.Format(_T("%d"), IdList[i][0]);
			tempSelect = selectString[1];
			tempSelect += _T(" where Judge.ID = '");
			tempSelect += str + _T("'");

			m_judgeAnswer = new JudgeQuestion(&questionDataBase);
			m_judgeAnswer->Open(CRecordset::forwardOnly, tempSelect);

			short nFields = m_judgeAnswer->GetODBCFieldCount();
			for (short index = 0; index < nFields; ++index) {
				m_judgeAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, i, str);
			}
		}
	}
	break;
	case IDC_RADIO2:
	{
		for (int i = 0; i < numRows; ++i) {
			str.Format(_T("%d"), IdList[i][0]);
			tempSelect = selectString[3];
			tempSelect += _T(" where Onechoice.ID = '");
			tempSelect += str + _T("'");

			m_oneAnswer = new OnechoiceQuestion(&questionDataBase);
			m_oneAnswer->Open(CRecordset::forwardOnly, tempSelect);

			short nFields = m_oneAnswer->GetODBCFieldCount();
			for (short index = 0; index < nFields; ++index) {
				m_oneAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, i, str);
			}
		}
	}
	break;
	case IDC_RADIO3:
	{
		for (int i = 0; i < numRows; ++i) {
			str.Format(_T("%d"), IdList[i][0]);
			tempSelect = selectString[5];
			tempSelect += _T(" where Morechoice.ID = '");
			tempSelect += str + _T("'");

			m_moreAnswer = new MorechoiceQuestion(&questionDataBase);
			m_moreAnswer->Open(CRecordset::forwardOnly, tempSelect);

			short nFields = m_moreAnswer->GetODBCFieldCount();
			for (short index = 0; index < nFields; ++index) {
				m_moreAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, i, str);
			}
		}
	}
	break;
	case IDC_RADIO4:
	{
		for (int i = 0; i < numRows; ++i) {
			str.Format(_T("%d"), IdList[i][0]);
			tempSelect = selectString[7];
			tempSelect += _T(" where Short.ID = '");
			tempSelect += str + _T("'");

			m_shortAnswer = new ShortQuestion(&questionDataBase);
			m_shortAnswer->Open(CRecordset::forwardOnly, tempSelect);

			short nFields = m_shortAnswer->GetODBCFieldCount();
			for (short index = 0; index < nFields; ++index) {
				m_shortAnswer->GetFieldValue(index, str);
				if (index == (nFields - 1)) {
					index = 7;
				}
				m_items.SetCellText(index, i, str);
			}
		}
	}
	break;
	default:break;
	}

}