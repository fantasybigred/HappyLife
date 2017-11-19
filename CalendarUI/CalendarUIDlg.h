
// CalendarUIDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include "../LunarCalendar/lunar_date.h"

// CCalendarUIDlg �Ի���
class CCalendarUIDlg : public CDialogEx
{
// ����
public:
	CCalendarUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALENDARUI_DIALOG };
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
public:
	afx_msg void OnEnChangeEdit2();
public:
	void get_total_years(std::vector<WORD>& years);
	void bind_years(CComboBox* combox);
	void bind_months(CComboBox* combox);
	//WORD get_weekday_by_gregorian_date(const date_info&  gregorian_date);
	void set_days_on_panel(CComboBox* combox, const date_info&  gregorian_date);
	void display_current_month_on_pannel(const date_info&  cur_date);
private:
	date_info get_pre_month(const date_info&  cur_date);
	date_info get_next_month(const date_info&  cur_date);
private:
	CFont m_Font;
public:
	afx_msg void OnBnClickedBtnPreMonth();
	afx_msg void OnBnClickedBtnNextMonth();
	afx_msg void OnBnClickedBtnReturnToday();
	afx_msg void OnCbnSelchangeComboYear();
	afx_msg void OnCbnSelchangeComboMonth();
	afx_msg void OnEnSetfocusDate();
};
