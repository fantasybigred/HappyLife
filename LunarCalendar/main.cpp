#include "lunar_date.h"
#include <iostream>

using namespace std;

//int main()
//{
//	//for (int i = 1; i <= 12; ++i)
//	//{
//	//	date_info date(1902, i, 18);
//	//	//date_info date(1901, 1, 1);
//	//	//date_info date(2017, 5, 15);
//	//	lunar_date lunar(date);
//	//	date_info l_date = lunar.get_lunar_date();
//	//	bool is_leap_month = lunar.is_leap_month();
//	//	bool is_big_month = lunar.is_big_month();
//	//	cout << "阳历日期为： " << (WORD)date.m_year << "年" << (WORD)date.m_month << "月" << (WORD)date.m_day << "日" << endl;
//	//	cout << "农历年份为： " << (WORD)l_date.m_year << endl;
//	//	cout << "农历月份为： " << (WORD)l_date.m_month << endl;
//	//	cout << "农历日期为： " << (WORD)l_date.m_day << endl;
//	//	cout << "是否为闰月： " << (is_leap_month ? "是" : "否") << endl;
//	//	cout << "是否为大月： " << (is_big_month ? "是" : "否") << endl;
//	//	cout << endl;
//	//}
//
//	//for (int i = 1; i <= 28; ++i)
//	//{
//	//	date_info date(1902, 2, i);
//	//	//date_info date(1901, 1, 1);
//	//	//date_info date(2017, 5, 15);
//	//	lunar_date lunar(date);
//	//	date_info l_date = lunar.get_lunar_date();
//	//	bool is_leap_month = lunar.is_leap_month();
//	//	bool is_big_month = lunar.is_big_month();
//	//	cout << "阳历日期为： " << (WORD)date.m_year << "年" << (WORD)date.m_month << "月" << (WORD)date.m_day << "日" << endl;
//	//	cout << "农历年份为： " << (WORD)l_date.m_year << endl;
//	//	cout << "农历月份为： " << (WORD)l_date.m_month << endl;
//	//	cout << "农历日期为： " << (WORD)l_date.m_day << endl;
//	//	cout << "是否为闰月： " << (is_leap_month ? "是" : "否") << endl;
//	//	cout << "是否为大月： " << (is_big_month ? "是" : "否") << endl;
//	//	cout << endl;
//	//}
//
//	//date_info date(2009, 1, 26);
//	//lunar_date lunar(date);
//	//date_info l_date = lunar.get_lunar_date();
//	//bool is_leap_month = lunar.is_leap_month();
//	//bool is_big_month = lunar.is_big_month();
//	//cout << "阳历日期为： " << (WORD)date.m_year << "年" << (WORD)date.m_month << "月" << (WORD)date.m_day << "日" << endl;
//	////cout << "农历年份为： " << (WORD)l_date.m_year << endl;
//	////cout << "农历月份为： " << (WORD)l_date.m_month << endl;
//	////cout << "农历日期为： " << (WORD)l_date.m_day << endl;
//	////cout << "是否为闰月： " << (is_leap_month ? "是" : "否") << endl;
//	////cout << "是否为大月： " << (is_big_month ? "是" : "否") << endl;
//	////cout << "农历" << lunar.get_tian_gan() << lunar.get_di_zhi() << "年，生肖" << lunar.get_sheng_xiao() << endl;
//	////cout << "干支月为： " << lunar.get_gan_zhi_month() << endl;
//	////cout << "干支日为： " << lunar.get_gan_zhi_day() << endl;
//	////cout << "农历日期为： " << lunar.get_tian_gan() << lunar.get_di_zhi() << "年，生肖" << lunar.get_sheng_xiao() << ", " << (WORD)l_date.m_month << "月, " << (WORD)l_date.m_day << "日";
//	//cout << lunar.get_lunar_date_by_string() << endl;
//	//cout << endl;
//
//	for (int i = 1; i <= 30; ++i)
//	{
//		date_info date(2017, 5, i);
//		cout << "阳历日期为： " << (WORD)date.m_year << "年" << (WORD)date.m_month << "月" << (WORD)date.m_day << "日" << endl;
//		lunar_date lunar(date);
//		date_info l_date = lunar.get_lunar_date();
//		cout << lunar.get_lunar_date_by_string() << endl;
//		cout << endl;
//	}
//
//	system("pause");
//	return 0;
//}