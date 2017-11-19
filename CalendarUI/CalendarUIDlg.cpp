
// CalendarUIDlg.cpp : ʵ���ļ�
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


// CCalendarUIDlg �Ի���



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


// CCalendarUIDlg ��Ϣ�������

BOOL CCalendarUIDlg::OnInitDialog()
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

	m_Font.DeleteObject();
	m_Font.CreatePointFont(120, _T("����"));

	CComboBox *combo_year = (CComboBox*)GetDlgItem(IDC_COMBO_YEAR);
	bind_years(combo_year);

	CComboBox *combo_month = (CComboBox*)GetDlgItem(IDC_COMBO_MONTH);
	bind_months(combo_month);

	CTime m_time;
	m_time = CTime::GetCurrentTime();
	date_info cur_date(m_time.GetYear(), m_time.GetMonth(), m_time.GetDay());

	date_process_unit process_unit;

	WORD first_day_of_month = process_unit.get_weekday_by_gregorian_date(date_info(cur_date.get_year(), cur_date.get_month(), 1));//��ǰ�·ݵ�1�������ڼ�
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
		edit_day->SetFont(&m_Font);//��������
		CString str;
		//str.Format(_T("%d"), i - IDC_DATE1 + 1);
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}

	//����1��ǰ����ϸ��µ�����
	date_info pre_month = get_pre_month(cur_date);
	WORD pre_month_days= process_unit.get_cur_month_days(pre_month);
	for (WORD i = 0; i < first_day_of_month - 1; ++i)
	{
		WORD edit_id = IDC_DATE1 + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//��������
		CString str;
		str.Format(_T("%d"), pre_month_days - first_day_of_month + i + 2);
		edit_day->SetWindowText(str);
	}

	//������β������¸��µ�����
	//date_info next_month = get_next_month(cur_date);
	//WORD next_month_days = process_unit.get_cur_month_days(next_month);
	for (WORD i = 0; i < 42 - days_of_month - (first_day_of_month - 1); ++i)
	{
		WORD edit_id = IDC_DATE1 + (first_day_of_month - 1) + days_of_month + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//��������
		CString str;
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCalendarUIDlg::OnPaint()
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
HCURSOR CCalendarUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalendarUIDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CCalendarUIDlg::get_total_years(std::vector<WORD>& years)
{
	CTime m_time;
	m_time = CTime::GetCurrentTime();             //��ȡ��ǰʱ������  
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
	m_time = CTime::GetCurrentTime();             //��ȡ��ǰʱ������  
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
	m_time = CTime::GetCurrentTime();             //��ȡ��ǰʱ������  
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

	WORD first_day_of_month = process_unit.get_weekday_by_gregorian_date(date_info(gregorian_date.get_year(), gregorian_date.get_month(), 1));//��ǰ�·ݵ�1�������ڼ�
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
		edit_day->SetFont(&m_Font);//��������
		CString str;
		str.Format(_T("%d"), i - IDC_DATE1 + 1);
		edit_day->SetWindowText(str);
	}
}



void CCalendarUIDlg::OnBnClickedBtnPreMonth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	WORD first_day_of_month = process_unit.get_weekday_by_gregorian_date(date_info(cur_date.get_year(), cur_date.get_month(), 1));//��ǰ�·ݵ�1�������ڼ�

	WORD days_of_month = process_unit.get_cur_month_days(cur_date);
	//���õ�ǰ�·ݵ�����
	for (WORD i = 0; i < days_of_month; ++i)
	{
		//CEdit *edit_day = (CEdit *)GetDlgItem(i);
		WORD edit_id = IDC_DATE1 + i + first_day_of_month - 1;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//��������
		CString str;
		//str.Format(_T("%d"), i - IDC_DATE1 + 1);
		str.Format(_T("%d"), i + 1);
		edit_day->SetWindowText(str);
	}

	//����1��ǰ����ϸ��µ�����
	date_info pre_month = get_pre_month(cur_date);
	WORD pre_month_days = process_unit.get_cur_month_days(pre_month);
	for (WORD i = 0; i < first_day_of_month - 1; ++i)
	{
		WORD edit_id = IDC_DATE1 + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//��������
		CString str;
		str.Format(_T("%d"), pre_month_days - first_day_of_month + i + 2);
		edit_day->SetWindowText(str);
	}

	//������β������¸��µ�����
	for (WORD i = 0; i < 42 - days_of_month - (first_day_of_month - 1); ++i)
	{
		WORD edit_id = IDC_DATE1 + (first_day_of_month - 1) + days_of_month + i;
		CEdit *edit_day = (CEdit*)GetDlgItem(edit_id);
		edit_day->SetFont(&m_Font);//��������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCalendarUIDlg::OnEnSetfocusDate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("HelloWorld!"));
}
