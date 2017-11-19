#pragma once
#include "calendar_const.h"

class date_process_unit
{
public:
	date_process_unit();
	date_process_unit(const date_info&  gregorian_date);	
	
public:
	static bool is_gregorian_leap_year(WORD year) { return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0); }
	WORD get_weekday_by_gregorian_date(const date_info & gregorian_date);
	static WORD get_cur_month_days(const date_info&  gregorian_date);
public:
	date_info get_lunar_date()const;
	date_info get_gregorian_date()const;
	std::string get_lunar_date_by_string()const;
	BYTE get_weekday_index()const { return m_weekday; }
	std::string get_weekday_by_string()const { return m_str_weekday; }
	bool is_leap_month()const { return m_is_leap_month; }
	bool is_big_month()const { return m_is_big_month; }
	std::string get_tian_gan()const { return m_tian_gan; }
	std::string get_di_zhi()const { return m_di_zhi; }
	std::string get_sheng_xiao()const { return m_sheng_xiao; }
	std::string get_gan_zhi_month()const { return m_gan_zhi_month; }
	std::string get_gan_zhi_day()const { return m_gan_zhi_day; }
	std::string cal_gan_zhi_month(WORD tian_gan_index, const date_info& l_date);
	std::string cal_gan_zhi_day(const date_info&  gregorian_date);
	WORD get_total_days_by_gregorian_date(const date_info&  gregorian_date, WORD& total_days);

private:	
	WORD convert_gregorian_to_lunar(const date_info&  gregorian_date);
	WORD get_days_of_lunar_year_by_hex(WORD hex);
	WORD get_lunar_leap_year_month(WORD hex) { return hex & 0xf; }
	WORD cal_tian_gan_and_di_zhi(const date_info& lunar_date, const date_info&  gregorian_date);
	//WORD get_weekday_by_gregorian_date(const date_info & gregorian_date);
private:
	date_info m_gregorian_date;
	date_info m_lunar_date;
	bool m_is_leap_month;
	bool m_is_big_month;
	std::string m_tian_gan;//天干
	std::string m_di_zhi;//地支
	std::string m_sheng_xiao;//生肖
	std::string m_gan_zhi_month;//干支月份
	std::string m_gan_zhi_day;//干支日
	BYTE m_weekday;
	std::string m_str_weekday;
};


//class date_info
//{
//public:
//	WORD m_gregorian_year;
//	BYTE m_gregorian_month;
//	BYTE m_gregorian_day;
//	WORD m_lunar_year;
//	BYTE m_lunar_month;
//	BYTE m_lunar_day;
//	BYTE m_weekday;
//	BYTE m_hour;
//	BYTE m_minute;
//	BYTE m_second;
//	date_info() :
//		m_gregorian_year(1900), m_gregorian_month(1), m_gregorian_day(31), 
//		m_lunar_year(0), m_lunar_month(1), m_lunar_day(1), 
//		m_weekday(3), 
//		m_hour(0), m_minute(0), m_second(0) {}
//	date_info(WORD year, BYTE month, BYTE day, bool is_gregorian_date = false) :
//		m_weekday(0),
//		m_hour(0), m_minute(0), m_second(0)
//	{
//		if (is_gregorian_date)
//		{
//			m_gregorian_year = year;
//			m_gregorian_month = month;
//			m_gregorian_day = day;
//			m_lunar_year = 0;
//			m_lunar_month = 0;
//			m_lunar_day = 0;
//		}
//		else
//		{
//			m_gregorian_year = 0;
//			m_gregorian_month = 0;
//			m_gregorian_day = 0;
//			m_lunar_year = year;
//			m_lunar_month = month;
//			m_lunar_day = day;
//		}
//	}
//	date_info(WORD year, BYTE month, BYTE day, BYTE hour, BYTE minute, BYTE second, bool is_gregorian_date = false)
//	{
//		date_info(year, month, day, is_gregorian_date);
//		m_hour = hour;
//		m_minute = minute;
//		m_second = second;
//		m_weekday = 0;
//	}
//	date_info(const date_info& date)
//	{
//		m_gregorian_year = date.m_gregorian_year;
//		m_gregorian_month = date.m_gregorian_month;
//		m_gregorian_day = date.m_gregorian_day;
//		m_lunar_year =  date.m_lunar_year;
//		m_lunar_month = date.m_lunar_month;
//		m_lunar_day = date.m_lunar_day;
//		m_hour = date.m_hour;
//		m_minute = date.m_minute;
//		m_second = date.m_second;
//		m_weekday = date.m_weekday;
//	}	
//	date_info operator = (const date_info& date)
//	{
//		m_gregorian_year = date.m_gregorian_year;
//		m_gregorian_month = date.m_gregorian_month;
//		m_gregorian_day = date.m_gregorian_day;
//		m_lunar_year = date.m_lunar_year;
//		m_lunar_month = date.m_lunar_month;
//		m_lunar_day = date.m_lunar_day;
//		m_hour = date.m_hour;
//		m_minute = date.m_minute;
//		m_second = date.m_second;
//		m_weekday = date.m_weekday;
//		return *this;
//	}
//	bool operator ==  (const date_info& date)const
//	{
//		return
//			m_gregorian_year == date.m_gregorian_year&&
//			m_gregorian_month == date.m_gregorian_month&&
//			m_gregorian_day == date.m_gregorian_day&&
//			m_lunar_year == date.m_lunar_year&&
//			m_lunar_month == date.m_lunar_month&&
//			m_lunar_day == date.m_lunar_day&&
//			m_hour == date.m_hour&&
//			m_minute == date.m_minute&&
//			m_second == date.m_second&&
//			m_weekday == date.m_weekday;
//	}
//
//	void initialize(WORD year, BYTE month, BYTE day, bool is_gregorian_date = false)
//	{
//		if (is_gregorian_date)
//		{
//			m_gregorian_year = year;
//			m_gregorian_month = month;
//			m_gregorian_day = day;
//			m_lunar_year = 0;
//			m_lunar_month = 0;
//			m_lunar_day = 0;
//		}
//		else
//		{
//			m_gregorian_year = 0;
//			m_gregorian_month = 0;
//			m_gregorian_day = 0;
//			m_lunar_year = year;
//			m_lunar_month = month;
//			m_lunar_day = day;
//		}
//		m_hour = 0;
//		m_minute = 0;
//		m_second = 0;
//		m_weekday = 0;
//	}
//
//	date_info();
//	date_info()
//	date_info(const date_info&  gregorian_date);
//	WORD convert_gregorian_to_lunar(const date_info&  gregorian_date);
//	std::string get_date_info_by_string()const;
//public:
//	date_info get_date_info()const;
//	bool is_leap_month()const { return m_is_leap_month; }
//	bool is_big_month()const { return m_is_big_month; }
//	std::string get_tian_gan()const { return m_tian_gan; }
//	std::string get_di_zhi()const { return m_di_zhi; }
//	std::string get_sheng_xiao()const { return m_sheng_xiao; }
//	std::string get_gan_zhi_month()const { return m_gan_zhi_month; }
//	std::string get_gan_zhi_day()const { return m_gan_zhi_day; }
//	std::string cal_gan_zhi_month(WORD tian_gan_index, const date_info& l_date);
//	std::string cal_gan_zhi_day(const date_info&  gregorian_date);
//	WORD get_total_days_by_gregorian_date(const date_info&  gregorian_date, WORD& total_days);
//	bool is_gregorian_leap_year(WORD year) { return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0); }
//private:
//
//	WORD get_days_of_lunar_year_by_hex(WORD hex);
//	WORD get_lunar_leap_year_month(WORD hex) { return hex & 0xf; }
//	WORD cal_tian_gan_and_di_zhi(const date_info& date_info, const date_info&  gregorian_date);
//private:
//	date_info m_date_info;
//	bool m_is_leap_month;
//	bool m_is_big_month;
//	std::string m_tian_gan;//天干
//	std::string m_di_zhi;//地支
//	std::string m_sheng_xiao;//生肖
//	std::string m_gan_zhi_month;//干支月份
//	std::string m_gan_zhi_day;//干支日
//};