#pragma once

#include <windef.h>
#include <string>

//typedef unsigned char BYTE;
//typedef unsigned int WORD;


const WORD DATE_SUCESS = 0;
const WORD DATE_FAULT = 1;

//经过整理的150年内的阴历数据
//共15行，每行10个数据。每个数据代表一年，从阳历1900.1.31日起，为第一个数据年的开始，即阳历1900.1.31＝阴历0.1.1。150个数据可推150年的阴历，因此目前最大只能推算到2049年，以后的推导，还需要从天文台得到新的数据后才能推导，否则将出现误差。

//要推算阴历，关键是理解这些数据的意义。

//拿第一个数据来说，代表阳历1900.1.31为始的阴历0年，0x04bd8是5个16进制数，共20bit。

//前4位，即0在这一年是润年时才有意义，它代表这年润月的大小月，为1则润大月，为0则润小月。大月30天小月29天
//中间12位，即4bd，每位代表一个月，为1则为大月，为0则为小月。
//最后4位，即8，代表这一年的润月月份，为0则不润。首4位要与末4位搭配使用。

const unsigned int LUNAR_DATE_TABLE[150] = {
	0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
	0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
	0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
	0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,
	0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
	0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
	0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
	0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
	0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
	0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
	0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
	0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
	0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
	0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
	0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};

class date_info
{
private:
	WORD m_year;
	BYTE m_month;
	BYTE m_day;
	BYTE m_hour;
	BYTE m_minute;
	BYTE m_second;
public:
	WORD get_year()const { return m_year; }
	WORD get_month()const { return m_month; }
	WORD get_day()const { return m_day; }
	WORD get_hour()const { return m_hour; }
	WORD get_minute()const { return m_minute; }
	WORD get_second()const { return m_second; }
	date_info() :m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0), m_second(0) {}
	date_info(WORD year, BYTE month, BYTE day) :m_hour(0), m_minute(0), m_second(0)
	{
		m_year = year;
		m_month = month;
		m_day = day;
	}
	date_info(WORD year, BYTE month, BYTE day, BYTE hour, BYTE mintue, BYTE second)
	{
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = hour;
		m_minute = mintue;
		m_second = second;
	}
	date_info(const date_info& date)
	{
		m_year = date.m_year;
		m_month = date.m_month;
		m_day = date.m_day;
		m_hour = date.m_hour;
		m_minute = date.m_minute;
		m_second = date.m_second;
	}
	date_info operator = (const date_info& date)
	{
		m_year = date.m_year;
		m_month = date.m_month;
		m_day = date.m_day;
		m_hour = date.m_hour;
		m_minute = date.m_minute;
		m_second = date.m_second;
		return *this;
	}
	bool operator ==  (const date_info& date)const
	{
		return m_year == date.m_year&&
			m_month == date.m_month&&
			m_day == date.m_day&&
			m_hour == date.m_minute&&
			m_minute == date.m_minute&&
			m_second == date.m_second;
	}
	//bool is_equal_date(const date_info& date)const
	//{
	//	return m_year == date.m_year&&
	//		m_month == date.m_year&&
	//		m_day == date.m_year&&
	//		m_hour == date.m_year&&
	//		m_minute == date.m_year&&
	//		m_second == date.m_year;
	//}
	void initialize(WORD year, BYTE month, BYTE day)
	{
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = 0;
		m_minute = 0;
		m_second = 0;
	}
};

const date_info BEGIN_GREGORIAN_DATE = date_info(1900, 1, 31);
const date_info BEGIN_LUNAR_DATE = date_info(0, 1, 1);
const WORD GREGORIAN_LEAP_YEAR_DAYS_PER_MONTH[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
const WORD GREGORIAN_UNLEAP_YEAR_DAYS_PER_MONTH[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

const std::string TIAN_GAN_ARR[10] = { "甲","乙","丙","丁","戊","己","庚","辛","壬","癸" };
const std::string DI_ZHI_ARR[12] = { "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" };
const std::string SHENG_XIAO_ARR[12] = { "鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪" };

const WORD BEGIN_GREGORIAN_TIAN_GAN = 6;
const WORD BEGIN_GREGORIAN_DI_ZHI = 0;
const WORD BEGIN_GREGORIAN_SHENG_XIAO = 0;

const std::string LUNAR_MONTH_NAME[12] = { "正月","二月","三月","四月","五月","六月","七月","八月","九月","十月","冬月","腊月" };
const std::string GREGORIAN_MONTH_NAME[12] = { "1月","1月","3月","4月","5月","6月","7月","8月","9月","10月","11月","12月" };

const std::string LUNAR_DAY_NAME[30] = { "初一", "初二", "初三", "初四", "初五", "初六", "初七", "初八", "初九", "初十", "十一", "十二", "十三", "十四", "十五", "十六", "十七", "十八", "十九", "二十", "廿一", "廿二", "廿三", "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十"};

//干支纪月法 
const std::string GAN_ZHI_MONTH[5][12] = {
	{"丙寅","丁卯","戊辰","己巳","庚午","辛未","壬申","癸酉","甲戌","乙亥","丙子","丁丑"},//干支为甲、己的月份
	{"戊寅","己卯","庚辰","辛巳","壬午","癸未","甲申","乙酉","丙戌","丁亥","戊子","己丑"},//干支为乙、庚的月份
	{"庚寅","辛卯","壬辰","癸巳","甲午","乙未","丙申","丁酉","戊戌","己亥","庚子","辛丑"},//干支为丙、辛的月份
	{"壬寅","癸卯","甲辰","乙巳","丙午","丁未","戊申","己酉","庚戌","辛亥","壬子","癸丑"},//干支为丁、壬的月份
	{"甲寅","乙卯","丙辰","丁巳","戊午","己未","庚申","辛酉","壬戌","癸亥","甲子","乙丑"},//干支为戊、癸的月份
};

const std::string WEEKDAY_ARR[7] = { "星期日","星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };
const WORD BEGIN_WEEKDAY_INDEX = 3;