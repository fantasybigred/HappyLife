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
//	//	cout << "��������Ϊ�� " << (WORD)date.m_year << "��" << (WORD)date.m_month << "��" << (WORD)date.m_day << "��" << endl;
//	//	cout << "ũ�����Ϊ�� " << (WORD)l_date.m_year << endl;
//	//	cout << "ũ���·�Ϊ�� " << (WORD)l_date.m_month << endl;
//	//	cout << "ũ������Ϊ�� " << (WORD)l_date.m_day << endl;
//	//	cout << "�Ƿ�Ϊ���£� " << (is_leap_month ? "��" : "��") << endl;
//	//	cout << "�Ƿ�Ϊ���£� " << (is_big_month ? "��" : "��") << endl;
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
//	//	cout << "��������Ϊ�� " << (WORD)date.m_year << "��" << (WORD)date.m_month << "��" << (WORD)date.m_day << "��" << endl;
//	//	cout << "ũ�����Ϊ�� " << (WORD)l_date.m_year << endl;
//	//	cout << "ũ���·�Ϊ�� " << (WORD)l_date.m_month << endl;
//	//	cout << "ũ������Ϊ�� " << (WORD)l_date.m_day << endl;
//	//	cout << "�Ƿ�Ϊ���£� " << (is_leap_month ? "��" : "��") << endl;
//	//	cout << "�Ƿ�Ϊ���£� " << (is_big_month ? "��" : "��") << endl;
//	//	cout << endl;
//	//}
//
//	//date_info date(2009, 1, 26);
//	//lunar_date lunar(date);
//	//date_info l_date = lunar.get_lunar_date();
//	//bool is_leap_month = lunar.is_leap_month();
//	//bool is_big_month = lunar.is_big_month();
//	//cout << "��������Ϊ�� " << (WORD)date.m_year << "��" << (WORD)date.m_month << "��" << (WORD)date.m_day << "��" << endl;
//	////cout << "ũ�����Ϊ�� " << (WORD)l_date.m_year << endl;
//	////cout << "ũ���·�Ϊ�� " << (WORD)l_date.m_month << endl;
//	////cout << "ũ������Ϊ�� " << (WORD)l_date.m_day << endl;
//	////cout << "�Ƿ�Ϊ���£� " << (is_leap_month ? "��" : "��") << endl;
//	////cout << "�Ƿ�Ϊ���£� " << (is_big_month ? "��" : "��") << endl;
//	////cout << "ũ��" << lunar.get_tian_gan() << lunar.get_di_zhi() << "�꣬��Ф" << lunar.get_sheng_xiao() << endl;
//	////cout << "��֧��Ϊ�� " << lunar.get_gan_zhi_month() << endl;
//	////cout << "��֧��Ϊ�� " << lunar.get_gan_zhi_day() << endl;
//	////cout << "ũ������Ϊ�� " << lunar.get_tian_gan() << lunar.get_di_zhi() << "�꣬��Ф" << lunar.get_sheng_xiao() << ", " << (WORD)l_date.m_month << "��, " << (WORD)l_date.m_day << "��";
//	//cout << lunar.get_lunar_date_by_string() << endl;
//	//cout << endl;
//
//	for (int i = 1; i <= 30; ++i)
//	{
//		date_info date(2017, 5, i);
//		cout << "��������Ϊ�� " << (WORD)date.m_year << "��" << (WORD)date.m_month << "��" << (WORD)date.m_day << "��" << endl;
//		lunar_date lunar(date);
//		date_info l_date = lunar.get_lunar_date();
//		cout << lunar.get_lunar_date_by_string() << endl;
//		cout << endl;
//	}
//
//	system("pause");
//	return 0;
//}