#include "lunar_date.h"
#include <iostream>

date_process_unit::date_process_unit()
{
	m_lunar_date.initialize(0, 0, 0);
	m_is_big_month = false;
	m_is_leap_month = false;
}

date_process_unit::date_process_unit(const date_info& gregorian_date)
{
	convert_gregorian_to_lunar(gregorian_date);
	m_weekday = get_weekday_by_gregorian_date(gregorian_date);
	m_str_weekday = WEEKDAY_ARR[m_weekday];
}

date_info date_process_unit::get_lunar_date()const
{
	return m_lunar_date;
}

date_info date_process_unit::get_gregorian_date()const
{
	return m_gregorian_date;
}

std::string date_process_unit::get_lunar_date_by_string()const
{
	return "农历日期为： " + LUNAR_MONTH_NAME[m_lunar_date.get_month() - 1] + LUNAR_DAY_NAME[m_lunar_date.get_day() - 1] + " 【" + get_tian_gan() + get_di_zhi() + "年，生肖" + get_sheng_xiao() + ", " + get_gan_zhi_month() + "月，" + get_gan_zhi_day() + "日" + "】";
}

WORD date_process_unit::convert_gregorian_to_lunar(const date_info & gregorian_date)
{
	WORD total_days = 0;
	WORD ret = get_total_days_by_gregorian_date(gregorian_date, total_days);
	if (ret == DATE_FAULT)return DATE_FAULT;
	//if (gregorian_date.is_equal_date(BEGIN_GREGORIAN_DATE))
	//if (gregorian_date == BEGIN_GREGORIAN_DATE)
	//{
	//	m_lunar_date = BEGIN_LUNAR_DATE;
	//	m_is_big_month = false;
	//	m_is_leap_month = false;
	//	return DATE_SUCESS;
	//}
	for (WORD year = 0; year < 150; ++year)
	{
		WORD days_of_year = get_days_of_lunar_year_by_hex(LUNAR_DATE_TABLE[year]);
		if (total_days <= days_of_year)
		{
			//WORD total_days;
			WORD leap_month = get_lunar_leap_year_month(LUNAR_DATE_TABLE[year]);
			WORD months = (LUNAR_DATE_TABLE[year] >> 4) & 0xfff;
			//std::cout << (LUNAR_DATE_TABLE[year]>>4) << "\t"<<months << std::endl;
			for (WORD month = 1; month <= 12; ++month)
			{
				//BYTE m = (months >> (month - 1)) & 0x1;//12bit月份顺序弄反了，应该是左边第一位是第一个月
				//BYTE m = (months >> (12 - month)) & 0x800;
				BYTE m = (months & (0x800 >> (month - 1))) > 0 ? 1 : 0;
				//std::cout << (WORD)m << std::endl;
				if (m == 1)
				{
					if (total_days <= 30)
					{
						m_lunar_date.initialize(year, month, total_days);
						m_is_big_month = true;
						m_is_leap_month = false;
						cal_tian_gan_and_di_zhi(m_lunar_date, gregorian_date);
						return DATE_SUCESS;
					}
					total_days -= 30;
					if (leap_month == month)
					{
						bool is_big_month = (get_lunar_leap_year_month(LUNAR_DATE_TABLE[year] >> 16)) == 1;
						WORD days_of_leap_month = is_big_month ? 30 : 29;
						if (total_days <= days_of_leap_month)
						{
							m_lunar_date.initialize(year, month, total_days);
							m_is_big_month = true;
							m_is_leap_month = true;
							cal_tian_gan_and_di_zhi(m_lunar_date, gregorian_date);
							return DATE_SUCESS;
						}
						total_days -= days_of_leap_month;
					}
				}
				else
				{
					if (total_days <= 29)
					{
						m_lunar_date.initialize(year, month, total_days);
						m_is_big_month = false;
						m_is_leap_month = false;
						cal_tian_gan_and_di_zhi(m_lunar_date, gregorian_date);
						return DATE_SUCESS;
					}
					total_days -= 29;
					if (leap_month == month)
					{
						bool is_big_month = (get_lunar_leap_year_month(LUNAR_DATE_TABLE[year] >> 16)) == 1;
						WORD days_of_leap_month = is_big_month ? 30 : 29;
						if (total_days <= days_of_leap_month)
						{
							m_lunar_date.initialize(year, month, total_days);
							m_is_big_month = false;
							m_is_leap_month = true;
							cal_tian_gan_and_di_zhi(m_lunar_date, gregorian_date);
							return DATE_SUCESS;
						}
						total_days -= days_of_leap_month;
					}
				}
			}
		}
		else
		{
			total_days -= days_of_year;
		}
	}
	return DATE_SUCESS;
}

//代表阳历1900.1.31为始的阴历0年
WORD date_process_unit::get_total_days_by_gregorian_date(const date_info&  gregorian_date, WORD& total_days)
{
	if (gregorian_date.get_year() < 1900)return DATE_FAULT;
	if (gregorian_date.get_month() < 1 || gregorian_date.get_month()>12) return DATE_FAULT;
	if (gregorian_date.get_day() < 1 || gregorian_date.get_day()>31) return DATE_FAULT;
	total_days = 0;
	if (gregorian_date.get_year() == 1900)
	{
		if (gregorian_date.get_month() == 1)
		{
			if (gregorian_date.get_day() != 31)return DATE_FAULT;
			total_days = 1;
			return DATE_SUCESS;
		}
		for (WORD i = 2; i < gregorian_date.get_month(); ++i)
		{
			total_days += GREGORIAN_UNLEAP_YEAR_DAYS_PER_MONTH[i - 1];
		}
		total_days += gregorian_date.get_day();
		total_days += 1;//加上1900.1.31这一天
		return DATE_SUCESS;
	}
	total_days += 335;
	for (WORD i = 1901; i < gregorian_date.get_year(); ++i)
	{
		if (is_gregorian_leap_year(i))
		{
			total_days += 366;
		}
		else
		{
			total_days += 365;
		}
	}

	for (WORD i = 1; i < gregorian_date.get_month(); ++i)
	{
		if (is_gregorian_leap_year(gregorian_date.get_year()))
		{
			total_days += GREGORIAN_LEAP_YEAR_DAYS_PER_MONTH[i - 1];
		}
		else
		{
			total_days += GREGORIAN_UNLEAP_YEAR_DAYS_PER_MONTH[i - 1];
		}
	}

	total_days += gregorian_date.get_day();
	return DATE_SUCESS;
}

WORD date_process_unit::get_days_of_lunar_year_by_hex(WORD hex)
{
	WORD total_days = 0;
	WORD leap_month = get_lunar_leap_year_month(hex);
	WORD months = (hex >> 4) & 0xfff;
	//std::cout << (hex >> 4) << "\t" << months << std::endl;
	for (WORD i = 1; i <= 12; ++i)
	{
		//BYTE m = (months >> (i - 1)) & 0x1;
		BYTE m = (months & (0x800 >> (i - 1))) > 0 ? 1 : 0;
		//std::cout << (WORD)m << std::endl;
		if (m == 1)
		{
			total_days += 30;

			if (leap_month == i)
			{
				bool is_big_month = (hex >> 16) == 1;
				total_days += is_big_month ? 30 : 29;
			}
				
		}
		else
		{
			total_days += 29;
			if (leap_month == i)
			{
				bool is_big_month = (hex >> 16) == 1;
				total_days += is_big_month ? 30 : 29;
			}
		}
	}
	//std::cout << "-----------------------------------------------" << std::endl;
	return total_days;
}

WORD date_process_unit::cal_tian_gan_and_di_zhi(const date_info& l_date, const date_info& gregorian_date)
{
	WORD tian_gan = (l_date.get_year() + BEGIN_GREGORIAN_TIAN_GAN) % 10;
	m_tian_gan = TIAN_GAN_ARR[tian_gan];
	WORD di_zhi = (l_date.get_year() + BEGIN_GREGORIAN_DI_ZHI) % 12;
	m_di_zhi = DI_ZHI_ARR[di_zhi];
	m_sheng_xiao = SHENG_XIAO_ARR[di_zhi];
	m_gan_zhi_month = cal_gan_zhi_month(tian_gan, l_date);
	m_gan_zhi_day = cal_gan_zhi_day(gregorian_date);
	return DATE_SUCESS;
}

std::string date_process_unit::cal_gan_zhi_month(WORD tian_gan_index, const date_info& l_date)
{
	return GAN_ZHI_MONTH[tian_gan_index % 5][l_date.get_month() - 1];//month为1-12，因此索引下标要减一
}

std::string date_process_unit::cal_gan_zhi_day(const date_info&  gregorian_date)
{
	//公式一：G = 4X + [X / 4] + 5Y + [Y / 4] + [3 * (M + 1) / 5] + D - 3

	//公式二：H = 8X + [X / 4] + 5Y + [Y / 4] + [3 * (M + 1) / 5] + D + 7 + I
	//G 除以10的余数是天干，H除以12的余数是地支。X是世纪数减一，Y是年份后两位，M 是月份，D是日数。奇数月i=0，偶数月i=6。
	//G = 4X + [X / 4] + 5Y + [Y / 4] + [3 * (M + 1) / 5] + D - 3
	//例如：2013年9月10日的干支日。 将数值代入计算公式。

	//G = 4 * 20 + [20 / 4] + 5 * 13 + [13 / 4] + [3 * (9 + 1) / 5] + 10 - 3 = 80 + 5 + 65 + 3 + 6 + 7 = 166。

	WORD X = gregorian_date.get_year() / 100;
	WORD Y = gregorian_date.get_year() % 100;
	WORD M = gregorian_date.get_month();
	WORD D = gregorian_date.get_day();
	WORD I = (M % 2 == 0 ? 6 : 0);

	WORD day_tian_gan = 4 * X + (X / 4) + 5 * Y + (Y / 4) + (3 * (M + 1) / 5) + D - 3;
	WORD day_di_zhi = 8 * X + (X / 4) + 5 * Y + (Y / 4) + (3 * (M + 1) / 5) + D + 7 + I;

	std::string day= TIAN_GAN_ARR[(day_tian_gan - 1) % 10] + DI_ZHI_ARR[(day_di_zhi - 1) % 12];

	return day;
}

WORD date_process_unit::get_weekday_by_gregorian_date(const date_info & gregorian_date)
{
	WORD total_days = 0;
	WORD week_day_index = 0;
	get_total_days_by_gregorian_date(gregorian_date, total_days);
	week_day_index = (total_days + BEGIN_WEEKDAY_INDEX - 1) % 7;
	return week_day_index;
}

WORD date_process_unit::get_cur_month_days(const date_info&  gregorian_date)
{
	WORD days_of_month = 0;
	if (is_gregorian_leap_year(gregorian_date.get_year()))
	{
		days_of_month = GREGORIAN_LEAP_YEAR_DAYS_PER_MONTH[gregorian_date.get_month() - 1];
	}
	else
	{
		days_of_month = GREGORIAN_UNLEAP_YEAR_DAYS_PER_MONTH[gregorian_date.get_month() - 1];
	}
	return days_of_month;
}