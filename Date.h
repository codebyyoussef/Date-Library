#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime> 
#include "MyString.h"
using namespace std;

class Date
{
private:
	short _day;
	short _month;
	short _year;

public:

	Date()
	{
		time_t currentTime = time(0);
		tm* localTime = localtime(&currentTime);

		_day = localTime->tm_mday;
		_month = localTime->tm_mon + 1;
		_year = localTime->tm_year + 1900;
	}
	Date(string date)
	{
		vector<string> dateComponents = MyString::splitString(date, "/");

		_day = stoi(dateComponents[0]);
		_month = stoi(dateComponents[1]);
		_year = stoi(dateComponents[2]);
	}
	Date(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}
	Date(short totalDays, short year)
	{
		*this = getDateFromTotalDays(totalDays, year);
		_day = this->day;
		_month = this->month;
		_year = this->year;
	}

	void setDay(short day)
	{
		_day = day;
	}
	short getDay()
	{
		return _day;
	}
	_declspec(property(get = getDay, put = setDay)) short day;

	void setMonth(short month)
	{
		_month = month;
	}
	short getMonth()
	{
		return _month;
	}
	_declspec(property(get = getMonth, put = setMonth)) short month;
	
	void setYear(short year)
	{
		_year = year;
	}
	short getYear()
	{
		return _year;
	}
	_declspec(property(get = getYear, put = setYear)) short year;

	void print()
	{
		cout << dateToString() << "\n";
	}

	static bool isLeapYear(short year)
	{
		return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	}
	bool isLeapYear()
	{
		return isLeapYear(_year);
	}

	static short numberOfDaysInAYear(short year)
	{
		return isLeapYear(year) ? 366 : 365;
	}
	short numberOfDaysInAYear()
	{
		return numberOfDaysInAYear(_year);
	}

	static short numberOfHoursInAYear(short year)
	{
		return numberOfDaysInAYear(year) * 24;
	}
	short numberOfHoursInAYear()
	{
		return numberOfHoursInAYear(_year);
	}

	static int numberOfMinutesInAYear(short year)
	{
		return numberOfHoursInAYear(year) * 60;
	}
	int numberOfMinutesInAYear()
	{
		return numberOfMinutesInAYear(_year);
	}

	static int numberOfSecondsInAYear(short year)
	{
		return numberOfMinutesInAYear(year) * 60;
	}
	int numberOfSecondsInAYear()
	{
		return numberOfSecondsInAYear(_year);
	}

	static short numberOfDaysInAMonth(short month, short year)
	{
		if (month < 1 || month > 12)
			return 0;

		short numberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return month == 2 ? (isLeapYear(year) ? 29 : 28) : numberOfDays[month - 1];
	}
	short numberOfDaysInAMonth()
	{
		return numberOfDaysInAMonth(_month, _year);
	}

	static short numberOfHoursInAMonth(short month, short year)
	{
		return numberOfDaysInAMonth(month, year) * 24;
	}
	short numberOfHoursInAMonth()
	{
		return numberOfHoursInAMonth(_month, _year);
	}

	static int numberOfMinutesInAMonth(short month, short year)
	{
		return numberOfHoursInAMonth(month, year) * 60;
	}
	int numberOfMinutesInAMonth()
	{
		return numberOfMinutesInAMonth(_month, _year);
	}

	static int numberOfSecondsInAMonth(short month, short year)
	{
		return numberOfMinutesInAMonth(month, year) * 60;
	}
	int numberOfSecondsInAMonth()
	{
		return numberOfSecondsInAMonth(_month, _year);
	}

	static short dayOfWeekOrder(short day, short month, short year)
	{
		short a, y, m, d;
		a = (14 - month) / 12;
		y = year - a;
		m = month + 12 * a - 2;
		// Gregorian:
		// 0:Sun, 1:Mon, 2:Tue...
		d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
		return d;
	}
	static short dayOfWeekOrder(Date date)
	{
		return dayOfWeekOrder(date.day, date.month, date.year);
	}
	short dayOfWeekOrder()
	{
		return dayOfWeekOrder(*this);
	}

	static string dayShortName(short dayOrder)
	{
		string daysOfTheWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		return daysOfTheWeek[dayOrder];
	}
	string dayShortName()
	{
		return dayShortName(dayOfWeekOrder());
	}

	static string monthShortName(short month)
	{
		string monthsOfTheYear[12] = { "Jan", "Fer", "Mar","Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return monthsOfTheYear[month - 1];
	}
	string monthShortName()
	{
		return monthShortName(_month);
	}

	static void printWeekDays()
	{
		string daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		for (short i = 0; i < 7; i++)
		{
			cout << daysOfTheWeek[i] << "  ";
		}
		cout << "\n  ";
	}

	static void printMonthCalendar(short month, short year)
	{
		// Index of the day from 0 to 6
		short current = dayOfWeekOrder(1, month, year);

		short numberOfDays = numberOfDaysInAMonth(month, year);

		// Print the current month name
		printf("  _____________%s_________________\n\n", monthShortName(month).c_str());

		// Print the columns
		printf("  Sun  Mon  Tue  Wen  Thu  Fri  Sat\n");

		// Print appropriate spaces
		short i;
		for (i = 0; i < current; i++)
		{
			printf("     ");
		}

		for (short j = 1; j <= numberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n");
	}
	void printMonthCalendar()
	{
		printMonthCalendar(_month, _year);
	}

	static void printYearCalendar(short year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d           ", year);
		printf("\n  _________________________________\n\n");

		const short numberOfMonts = 12;
		for (short month = 1; month <= numberOfMonts; month++)
		{
			printMonthCalendar(month, year);
		}
	}
	void printYearCalendar()
	{
		printYearCalendar(_year);
	}

	static short numberOfDaysFromTheBeginningOfTheYear(short day, short month, short year)
	{
		short totalDays = 0;

		for (short i = 1; i <= month - 1; i++)
		{
			totalDays += numberOfDaysInAMonth(i, year);
		}

		totalDays += day;

		return totalDays;
	}
	short numberOfDaysFromTheBeginningOfTheYear()
	{
		return numberOfDaysFromTheBeginningOfTheYear(_day, _month, _year);
	}

	static Date getDateFromTotalDays(short totalDays, short year)
	{
		Date date;

		short remainingDays = totalDays;
		short monthDays = 0;

		date.year = year;
		date.month = 1;

		while (true)
		{
			monthDays = numberOfDaysInAMonth(date.month, year);
			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				date.month++;
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}

	static Date addDaysToDate(short additionalDays, Date &date)
	{
		short remainingDays = additionalDays + numberOfDaysFromTheBeginningOfTheYear(date.day, date.month, date.year);
		short monthDays = 0;

		date.month = 1;

		while (true)
		{
			monthDays = numberOfDaysInAMonth(date.month, date.year);
			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				date.month++;

				if (date.month > 12)
				{
					date.month = 1;
					date.year++;
				}
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}
	void addDaysToDate(short additionalDays)
	{
		addDaysToDate(additionalDays, *this);
	}

	static bool isDate1LessThanDate2(Date date1, Date date2)
	{
		return date1.year < date2.year ? true : (date1.year == date2.year ? (date1.month < date2.month ? true : (date1.month == date2.month ? date1.day < date2.day : false)) : false);
	}
	bool isDateLessThanDate2(Date date2)
	{
		// note; *this sends current object
		return isDate1LessThanDate2(*this, date2);
	}

	static bool isDate1EqualToDate2(Date date1, Date date2)
	{                                                              
		return (date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day);
	}
	bool isDateEqualToDate2(Date date2)
	{
		return isDate1EqualToDate2(*this, date2);
	}

	static bool isLastDayInMonth(Date &date)
	{
		return date.day == numberOfDaysInAMonth(date.month, date.year);
	}
	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short month)
	{
		return month == 12;
	}
	bool isLastMonthInYear()
	{
		return _month == 12;
	}

	static Date increaseDateByOneDay(Date &date)
	{
		if (isLastDayInMonth(date))
		{
			if (isLastMonthInYear(date.month))
			{
				date.day = 1;
				date.month = 1;
				date.year++;
			}
			else
			{
				date.day = 1;
				date.month++;
			}
		}
		else
		{
			date.day++;
		}
		return date;
	}
	void increaseDateByOneDay()
	{
		increaseDateByOneDay(*this);
	}

	static void swapDates(Date& date1, Date& date2)
	{
		Date tempDate;
		tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}
	void swapDates(Date& date2)
	{
		swapDates(*this, date2);
	}

	static int getDifferenceInDays(Date date1, Date date2, bool includeEndDay = false)
	{
		int days = 0;
		short swapFlagValue = 1;

		if (!isDate1LessThanDate2(date1, date2) && !isDate1EqualToDate2(date1, date2))
		{
			swapDates(date1, date2);
			swapFlagValue = -1;
		}

		while (isDate1LessThanDate2(date1, date2))
		{
			days++;
			date1 = increaseDateByOneDay(date1);
		}

		if (includeEndDay == false)
			days--;

		return days * swapFlagValue;
	}
	int getDifferenceInDays(Date date2, bool includeEndDay = false)
	{
		return getDifferenceInDays(*this, date2, includeEndDay);
	}

	static Date getCurrentDate()
	{
		Date currentDate;
		time_t currentTime = time(0);
		tm* localTime = localtime(&currentTime);

		currentDate.year = localTime->tm_year + 1900;
		currentDate.month = localTime->tm_mon + 1;
		currentDate.day = localTime->tm_mday;

		return currentDate;
	}

	static short caluclateMyAgeInDays(Date birthDate)
	{
		return getDifferenceInDays(birthDate, getCurrentDate());
	}
	short caluclateMyAgeInDays()
	{
		return caluclateMyAgeInDays(*this);
	}

	static Date increaseDateByXDays(Date &date, short daysToAdd)
	{
		for (short i = 1; i <= daysToAdd; i++)
		{
			date = increaseDateByOneDay(date);
		}
		return date;
	}
	void increaseDateByXDays(short daysToAdd)
	{
		increaseDateByXDays(*this, daysToAdd);
	}

	static Date increaseDateByOneWeek(Date &date)
	{
		return increaseDateByXDays(date, 7);
	}
	void increaseDateByOneWeek()
	{
		increaseDateByOneWeek(*this);
	}

	static Date increaseDateByXWeeks(Date &date, short weeksToAdd)
	{
		for (short i = 1; i <= weeksToAdd; i++)
		{
			date = increaseDateByOneWeek(date);
		}
		return date;
	}
	void increaseDateByXWeeks(short weeksToAdd)
	{
		increaseDateByXWeeks(*this, weeksToAdd);
	}

	static Date increaseDateByOneMonth(Date &date)
	{
		if (date.month == 12)
		{
			date.month = 1;
			date.year++;
		}
		else
		{
			date.month++;
		}

		// last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should be 28/2/2022
		short numberOfDaysInCurrentMonth = numberOfDaysInAMonth(date.month, date.year);
		if (date.day > numberOfDaysInCurrentMonth)
		{
			date.day = numberOfDaysInCurrentMonth;
		}

		return date;
	}
	void increaseDateByOneMonth()
	{
		increaseDateByOneMonth(*this);
	}

	static Date increaseDateByXMonths(Date &date, short monthsToAdd)
	{
		for (short i = 1; i <= monthsToAdd; i++)
		{
			date = increaseDateByOneMonth(date);
		}
		return date;
	}
	void increaseDateByXMonths(short monthsToAdd)
	{
		increaseDateByXMonths(*this, monthsToAdd);
	}

	static Date increaseDateByOneYear(Date &date)
	{
		date.year++;
		return date;
	}
	void increaseDateByOneYear()
	{
		increaseDateByOneYear(*this);
	}

	static Date increaseDateByXYears(Date &date, short yearsToAdd)
	{
		date.year += yearsToAdd;
		return date;
	}
	void increaseDateByXYears(short yearsToAdd)
	{
		increaseDateByXYears(*this, yearsToAdd);
	}

	static Date increaseDateByOneDecade(Date &date)
	{
		date.year += 10;
		return date;
	}
	void increaseDateByOneDecade()
	{
		increaseDateByOneDecade(*this);
	}

	static Date increaseDateByXDecades(Date &date, short decadesToAdd)
	{
		date.year += decadesToAdd * 10;
		return date;
	}
	void increaseDateByXDecades(short decadesToAdd)
	{
		increaseDateByXDecades(*this, decadesToAdd);
	}

	static Date increaseDateByOneCentury(Date &date)
	{
		date.year += 100;
		return date;
	}
	void increaseDateByOneCentury()
	{
		increaseDateByOneCentury(*this);
	}

	static Date increaseDateByMillennium(Date &date)
	{
		date.year += 1000;
		return date;
	}
	void increaseDateByMillennium()
	{
		increaseDateByMillennium(*this);
	}

	static Date decreaseDateByOneDay(Date &date)
	{
		if (date.day == 1)
		{
			if (date.month == 1)
			{
				date.month = 12;
				date.day = 31;
				date.year--;
			}
			else
			{
				date.month--;
				date.day = numberOfDaysInAMonth(date.month, date.year);
			}
		}
		else
		{
			date.day--;
		}
		return date;
	}
	void decreaseDateByOneDay()
	{
		decreaseDateByOneDay(*this);
	}

	static Date decreaseDateByXDays(Date &date, short days)
	{
		for (short i = 1; i <= days; i++)
		{
			date = decreaseDateByOneDay(date);
		}
		return date;
	}
	void decreaseDateByXDays(short days)
	{
		decreaseDateByXDays(*this, days);
	}

	static Date decreaseDateByOneWeek(Date &date)
	{
		return decreaseDateByXDays(date, 7);
	}
	void decreaseDateByOneWeek()
	{
		decreaseDateByOneWeek(*this);
	}

	static Date decreaseDateByXWeeks(Date &date, short weeks)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = decreaseDateByOneWeek(date);
		}
		return date;
	}
	void decreaseDateByXWeeks(short weeks)
	{
		decreaseDateByXWeeks(*this, weeks);
	}

	static Date decreaseDateByOneMonth(Date &date)
	{
		if (date.month == 1)
		{
			date.month = 12;
			date.year--;
		}
		else
		{
			date.month--;
		}

		// last check day in date should not exceed max days in the current month
		// example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should be 28/2/2022
		short numberOfDaysInCurrentMonth = numberOfDaysInAMonth(date.month, date.year);
		if (date.day > numberOfDaysInCurrentMonth)
		{
			date.day = numberOfDaysInCurrentMonth;
		}
		return date;
	}
	void decreaseDateByOneMonth()
	{
		decreaseDateByOneMonth(*this);
	}

	static Date decreaseDateByXMonths(Date &date, short months)
	{
		for (short i = 1; i <= months; i++)
		{
			date = decreaseDateByOneMonth(date);
		}
		return date;
	}
	void decreaseDateByXMonths(short months)
	{
		decreaseDateByXMonths(*this, months);
	}

	static Date decreaseDateByOneYear(Date &date)
	{
		date.year--;
		return date;
	}
	void decreaseDateByOneYear()
	{
		decreaseDateByOneYear(*this);
	}

	static Date decreaseDateByXYears(Date &date, short years)
	{
		date.year -= years;
		return date;
	}
	void decreaseDateByXYears(short years)
	{
		decreaseDateByXYears(*this, years);
	}

	static Date decreaseDateByOneDecade(Date &date)
	{
		date.year -= 10;
		return date;
	}
	void decreaseDateByOneDecade()
	{
		decreaseDateByOneDecade(*this);
	}

	static Date decreaseDateByXDecades(Date &date, short decades)
	{
		date.year -= decades * 10;
		return date;
	}
	void decreaseDateByXDecades(short decades)
	{
		decreaseDateByXDecades(*this, decades);
	}

	static Date decreaseDateByOneCentury(Date &date)
	{
		date.year -= 100;
		return date;
	}
	void decreaseDateByOneCentury()
	{
		decreaseDateByOneCentury(*this);
	}

	static Date decreaseDateByMillennium(Date &date)
	{
		date.year -= 1000;
		return date;
	}
	void decreaseDateByMillennium()
	{
		decreaseDateByMillennium(*this);
	}

	static bool isEndOfWeek(Date date)
	{
		return dayOfWeekOrder(date) == 0;
	}
	bool isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(Date date)
	{
		// weekends are Sat and Sun
		short dayIndex = dayOfWeekOrder(date);
		return dayIndex == 6 || dayIndex == 0;
	}
	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(Date date)
	{
		return !isWeekEnd(date);
	}
	bool isBusinessDay()
	{
		return isBusinessDay(*this);
	}

	static short daysUntilTheEndOfWeek(Date date)
	{
		return 6 - dayOfWeekOrder(date);
	}
	short daysUntilTheEndOfWeek()
	{
		return daysUntilTheEndOfWeek(*this);
	}

	static short daysUntilTheEndOfMonth(Date date)
	{
		return numberOfDaysInAMonth(date.month, date.year) - date.day;
	}
	short daysUntilTheEndOfMonth()
	{
		return daysUntilTheEndOfMonth(*this);
	}

	short daysUntilTheEndOfYear(Date date)
	{
		short numberOfDaysInYear = isLeapYear(date.year) ? 366 : 365;
		short totalDays = numberOfDaysFromTheBeginningOfTheYear(date.day, date.month, date.year);
		return numberOfDaysInYear - totalDays;
	}
	short daysUntilTheEndOfYear()
	{
		return daysUntilTheEndOfYear(*this);
	}

	static short calculateVacationDays(Date dateFrom, Date dateTo)
	{
		short daysCount = 0;
		while (isDate1LessThanDate2(dateFrom, dateTo))
		{
			if (isBusinessDay(dateFrom))
			{
				daysCount++;
			}
			dateFrom = increaseDateByOneDay(dateFrom);
		}
		return daysCount;
	}
	short calculateVacationDays(Date dateTo)
	{
		return calculateVacationDays(*this, dateTo);
	}

	/*static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);

	}*/

	static Date calculateVacationReturnDate(Date dateFrom, short vacationDays)
	{
		short weekendCounter = 0;

		//in case the data  is weekend keep adding one day util you reach business day
		//we get rid of all weekends before the first business day
		while (isWeekEnd(dateFrom))
		{
			dateFrom = increaseDateByOneDay(dateFrom);
		}

		//here we increase the vacation dates to add all weekends to it.
		for (short i = 1; i <= vacationDays + weekendCounter; i++)
		{
			if (isWeekEnd(dateFrom))
				weekendCounter++;

			dateFrom = increaseDateByOneDay(dateFrom);
		}

		//in case if return date is week end keep adding one day util you reach business day
		while (isWeekEnd(dateFrom))
		{
			dateFrom = increaseDateByOneDay(dateFrom);
		}

		return dateFrom;
	}
	Date calculateVacationReturnDate(short vacationDays)
	{
		return calculateVacationReturnDate(*this, vacationDays);
	}

	static bool isDate1BeforeDate2(Date date1, Date date2)
	{
		return date1.year < date2.year ? true : (date1.year == date2.year ? (date1.month < date2.month ? true : (date1.month == date2.month ? date1.day < date2.day : false)) : false);
	}
	bool isDateBeforeDate2(Date date2)
	{
		return isDate1BeforeDate2(*this, date2);
	}

	static bool isDate1AfterDate2(Date date1, Date date2)
	{
		return !isDate1BeforeDate2(date1, date2) && !isDate1EqualToDate2(date1, date2);
	}
	bool isDateAfterDate2(Date date2)
	{
		return isDate1AfterDate2(*this, date2);
	}

	enum enComparisonResult { Before = -1, Equal = 0, After = 1 };
	static enComparisonResult compareDates(Date date1, Date date2)
	{
		if (isDate1BeforeDate2(date1, date2))
			return Before;

		if (isDate1EqualToDate2(date1, date2))
			return Equal;

		return After;
	}
	enComparisonResult compareDates(Date date2)
	{
		return compareDates(*this, date2);
	}

	static bool isValidDate(Date date)
	{
		bool validMonth = (date.month > 0 && date.month <= 12);
		bool validDay = (date.day > 0 && date.day <= numberOfDaysInAMonth(date.month, date.year));
		bool validYear = (date.year > 0);
		return validMonth && validDay && validYear;
	}
	bool isValidDate()
	{
		return isValidDate(*this);
	}

	Date stringToDate(string dateStr)
	{
		Date date;
		vector<string> dateParts = MyString::splitString(dateStr, "/");

		date.day = stoi(dateParts[0]);
		date.month = stoi(dateParts[1]);
		date.year = stoi(dateParts[2]);

		return date;
	}
	static string dateToString(Date date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}
	string dateToString()
	{
		return dateToString(*this);
	}

	static string formatDate(Date date, string dateFormat = "dd/mm/yyyy")
	{
		string formattedDateString;
		formattedDateString = MyString::replaceSubstring(dateFormat, "dd", to_string(date.day));
		formattedDateString = MyString::replaceSubstring(formattedDateString, "mm", to_string(date.month));
		formattedDateString = MyString::replaceSubstring(formattedDateString, "yyyy", to_string(date.year));
		return formattedDateString;
	}
	string formatDate(string dateFormat = "dd/mm/yyyy")
	{
		return formatDate(*this, dateFormat);
	}
};


