
// CalendarUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CalendarUI.h"
#include "CalendarUIDlg.h"
#include "afxdialogex.h"
#include <windef.h>
//#include "lunar_date.h"
//#include "../LunarClaendar/lunar_date.h"



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


// CCalendarUIDlg 对话框



CCalendarUIDlg::CCalendarUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALENDARUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalendarUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalendarUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT2, &CCalendarUIDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BTN_PRE_MONTH, &CCalendarUIDlg::OnBnClickedBtnPreMonth)
	ON_BN_CLICKED(IDC_BTN_NEXT_MONTH, &CCalendarUIDlg::OnBnClickedBtnNextMonth)
	ON_BN_CLICKED(IDC_BTN_RETURN_TODAY, &CCalendarUIDlg::OnBnClickedBtnReturnToday)
	ON_CBN_SELCHANGE(IDC_COMBO_YEAR, &CCalendarUIDlg::OnCbnSelchangeComboYear)
	ON_CBN_SELCHANGE(IDC_COMBO_MONTH, &CCalendarUIDlg::OnCbnSelchangeComboMonth)
	ON_EN_SETFOCUS(IDC_DATE1, &CCalendarUIDlg::OnEnSetfocusDate)
END_MESSAGE_MAP()


// CCalendarUIDlg 消息处理程序

BOOL CCalendarUIDlg::OnInitDialog()
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

	m_Font.DeleteObject();
	m_Font.CreatePointFont(120, _T("黑体"));

	CComboBox *combo_year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	bind_years(combo_year);

	CComboBox *combo_month = (CComboBox*)GetDlgItem(IDC_COMBO_MONTH);
	bind_months(combo_month);

	CTime m_time;
	m_time = CTime::GetCurrentTime();
	date_info cur_date(m_time.GetYear(), m_time.GetMonth(), m_time.GetDay());

	date_process_unit process_unit;

	WORD first_day_of_month = process_unit.get_weekday_by_gregorian_date(date_info(cur_date.get_year(), cur_date.get_month(), 1));//当前月份的1号是星期几
	//WORD days_of_month = 0;
	//lunar_date lunar;
	//if (process_unit.is_gregorian_leap_year(cur_date.get_year()))
	//{
	//	days_of_month = GREGORIAN_LEAP_YEAR_DAYS_PER_MONTH[cur_date.get_month() - 1];
	//}
	//else
	//{
	//	days_of_month = GREGORIAN_UNLEAP_YEAR_DAYS_PER_MONTH[cur_date.get_month() - 1];
	//}

	WORD days_of_month = process_unit.get_cur_month_days(cur_date);

	//for (WORD i = IDC_DATE1 + first_day_of_month - 1; i < days_of_month + IDC_DATE1; ++i)
	for (WORD i = 0; i < days_of_month; ++i)
	{
		//CEdit *edit_day = (CEdit *)GetDlgItem(i);
		WORD edit_id = IDC_DATE1 + i + first_day_of_month - 1;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		//str.Format(_T("%d"), i - IDC_DATE1 + 1);
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}

	//设置1号前面的上个月的日期
	date_info pre_month = get_pre_month(cur_date);
	WORD pre_month_days= process_unit.get_cur_month_days(pre_month);
	for (WORD i = 0; i < first_day_of_month - 1; ++i)
	{
		WORD edit_id = IDC_DATE1 + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		str.Format(_T("%d"), pre_month_days - first_day_of_month + i + 2);
		edit_day->SetWindowText(str);
	}

	//设置月尾后面的下个月的日期
	//date_info next_month = get_next_month(cur_date);
	//WORD next_month_days = process_unit.get_cur_month_days(next_month);
	for (WORD i = 0; i < 42 - days_of_month - (first_day_of_month - 1); ++i)
	{
		WORD edit_id = IDC_DATE1 + (first_day_of_month - 1) + days_of_month + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalendarUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalendarUIDlg::OnPaint()
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
HCURSOR CCalendarUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalendarUIDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CCalendarUIDlg::get_total_years(std::vector<WORD>& years)
{
	CTime m_time;
	m_time = CTime::GetCurrentTime();             //获取当前时间日期  
	WORD cur_year = m_time.GetYear();
	//std::vector<WORD> years;
	for (WORD i = 0; i <= cur_year; ++i)
	{
		years.push_back(i);
	}
	//return years;
}

void CCalendarUIDlg::bind_years(CComboBox* combox)
{
	combox->ResetContent();
	CTime m_time;
	m_time = CTime::GetCurrentTime();             //获取当前时间日期  
	WORD cur_year = m_time.GetYear();

	CString str;
	for (WORD i = 1900; i <= cur_year; ++i)
	{
		str.Format(_T("%d"), i);
		combox->InsertString(i - 1900, str);
		//combox->AddString(str);
	}
	combox->SetCurSel(cur_year - 1900);
	//combox->SetCurSel(cur_year);
}

void CCalendarUIDlg::bind_months(CComboBox* combox)
{
	combox->ResetContent();
	CTime m_time;
	m_time = CTime::GetCurrentTime();             //获取当前时间日期  
	WORD cur_month = m_time.GetMonth();

	CString str;
	for (WORD i = 0; i < 12; ++i)
	{
		str = GREGORIAN_MONTH_NAME[i].c_str();

		combox->InsertString(i, str);
	}
	combox->SetCurSel(cur_month - 1);
	//combox->SetCurSel(cur_month);
}

//WORD CCalendarUIDlg::get_weekday_by_gregorian_date(const date_info & gregorian_date)
//{
//	WORD total_days = 0;
//	WORD week_day_index = 0;
//	lunar_date lunar;
//	
//	lunar.get_total_days_by_gregorian_date(gregorian_date, total_days);
//	week_day_index = (total_days + BEGIN_WEEKDAY_INDEX - 1) % 7;
//	return week_day_index;
//}

void CCalendarUIDlg::set_days_on_panel(CComboBox* combox, const date_info&  gregorian_date)
{
	//CTime m_time;
	//m_time = CTime::GetCurrentTime();
	//date_info cur_date(m_time.GetYear(), m_time.GetMonth(), m_time.GetDay());

	date_process_unit process_unit;

	WORD first_day_of_month = process_unit.get_weekday_by_gregorian_date(date_info(gregorian_date.get_year(), gregorian_date.get_month(), 1));//当前月份的1号是星期几
	WORD days_of_month = 0;
	//lunar_date lunar;
	if (process_unit.is_gregorian_leap_year(gregorian_date.get_year()))
	{
		days_of_month = GREGORIAN_LEAP_YEAR_DAYS_PER_MONTH[gregorian_date.get_month() - 1];
	}
	else
	{
		days_of_month = GREGORIAN_UNLEAP_YEAR_DAYS_PER_MONTH[gregorian_date.get_month() - 1];
	}
	for (WORD i = IDC_DATE1 + first_day_of_month - 1; i < days_of_month + IDC_DATE1; ++i)
	{
		CEdit *edit_day = (CEdit *)GetDlgItem(i);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		str.Format(_T("%d"), i - IDC_DATE1 + 1);
		edit_day->SetWindowText(str);
	}
}



void CCalendarUIDlg::OnBnClickedBtnPreMonth()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString year;
	//CString month;
	//CString day;
	//GetDlgItemText(IDC_COMBO_YEAR, year);
	//GetDlgItemText(IDC_COMBO_MONTH, month);
	CComboBox *combo_year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	CComboBox *combo_month = (CComboBox*)GetDlgItem(IDC_COMBO_MONTH);
	//int tmp1 = combo_year->GetCurSel();
	//int tmp2 = combo_month->GetCurSel();
	WORD year = combo_year->GetCurSel() + 1900;
	BYTE month = combo_month->GetCurSel() + 1;
	date_info cur_date(year, month, 1);
	date_info pre_date = get_pre_month(cur_date);
	display_current_month_on_pannel(pre_date);
	combo_year->SetCurSel(pre_date.get_year() - 1900);
	combo_month->SetCurSel(pre_date.get_month() - 1);
}

void CCalendarUIDlg::display_current_month_on_pannel(const date_info&  cur_date)
{
	date_process_unit process_unit;

	WORD first_day_of_month = process_unit.get_weekday_by_gregorian_date(date_info(cur_date.get_year(), cur_date.get_month(), 1));//当前月份的1号是星期几

	WORD days_of_month = process_unit.get_cur_month_days(cur_date);
	//设置当前月份的日期
	for (WORD i = 0; i < days_of_month; ++i)
	{
		//CEdit *edit_day = (CEdit *)GetDlgItem(i);
		WORD edit_id = IDC_DATE1 + i + first_day_of_month - 1;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		//str.Format(_T("%d"), i - IDC_DATE1 + 1);
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}

	//设置1号前面的上个月的日期
	date_info pre_month = get_pre_month(cur_date);
	WORD pre_month_days = process_unit.get_cur_month_days(pre_month);
	for (WORD i = 0; i < first_day_of_month - 1; ++i)
	{
		WORD edit_id = IDC_DATE1 + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		str.Format(_T("%d"), pre_month_days - first_day_of_month + i + 2);
		edit_day->SetWindowText(str);
	}

	//设置月尾后面的下个月的日期
	for (WORD i = 0; i < 42 - days_of_month - (first_day_of_month - 1); ++i)
	{
		WORD edit_id = IDC_DATE1 + (first_day_of_month - 1) + days_of_month + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//设置字体
		CString str;
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}
}

date_info CCalendarUIDlg::get_pre_month(const date_info&  cur_date)
{
	date_info pre_date;
	if (cur_date.get_month() > 1)
		pre_date.initialize(cur_date.get_year(), cur_date.get_month() - 1, cur_date.get_day());
	else
		pre_date.initialize(cur_date.get_year() - 1, 12, cur_date.get_day());
	return pre_date;
}

date_info CCalendarUIDlg::get_next_month(const date_info&  cur_date)
{
	date_info pre_date;
	if (cur_date.get_month() < 12)
		pre_date.initialize(cur_date.get_year(), cur_date.get_month() + 1, cur_date.get_day());
	else
		pre_date.initialize(cur_date.get_year() + 1, 1, cur_date.get_day());
	return pre_date;
}

void CCalendarUIDlg::OnBnClickedBtnNextMonth()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox *combo_year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	CComboBox *combo_month = (CComboBox*)GetDlgItem(IDC_COMBO_MONTH);
	WORD year = combo_year->GetCurSel() + 1900;
	BYTE month = combo_month->GetCurSel() + 1;
	date_info cur_date(year, month, 1);
	date_info next_date = get_next_month(cur_date);
	display_current_month_on_pannel(next_date);
	combo_year->SetCurSel(next_date.get_year() - 1900);
	combo_month->SetCurSel(next_date.get_month() - 1);

}


void CCalendarUIDlg::OnBnClickedBtnReturnToday()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox *combo_year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	CComboBox *combo_month = (CComboBox*)GetDlgItem(IDC_COMBO_MONTH);
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	date_info cur_date(m_time.GetYear(), m_time.GetMonth(), m_time.GetDay());
	display_current_month_on_pannel(cur_date);
	combo_year->SetCurSel(cur_date.get_year() - 1900);
	combo_month->SetCurSel(cur_date.get_month() - 1);
}


void CCalendarUIDlg::OnCbnSelchangeComboYear()
{
	// TODO: 在此添加控件通知处理程序代码
	//CComboBox *combo_year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	//CComboBox *combo_month = (CComboBox*)GetDlgItem(IDC_COMBO_MONTH);
	//WORD year = combo_year->GetCurSel() + 1900;
	//BYTE month = combo_month->GetCurSel() + 1;
	//date_info cur_date(year, month, 1);
	//date_info next_date = get_next_month(cur_date);
	//display_current_month_on_pannel(next_date);
	//combo_year->SetCurSel(next_date.get_year() - 1900);
	//combo_month->SetCurSel(next_date.get_month() - 1);
}


void CCalendarUIDlg::OnCbnSelchangeComboMonth()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCalendarUIDlg::OnEnSetfocusDate()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("HelloWorld!"));
}
