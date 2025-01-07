# Date-Library

This is a C++ Date library that provides comprehensive functionality for working with dates. It includes features for manipulating, comparing, formatting, and performing calculations on dates. The library supports operations like adding/subtracting days, weeks, months, years, and even centuries, alongside checking leap years, calculating the difference between dates, and determining weekdays.

## Features

* Date Initialization:
    * Initialize the Date object with the current date (default constructor).
    * Initialize a Date object from a string (format: "dd/mm/yyyy").
    * Initialize with day, month, and year parameters.
    * Initialize with the total number of days in a year and a year.

* Date Components:
    * Access and set individual components of the date (day, month, year).
    * Built-in properties (day, month, year) for convenient manipulation.

* Date Operations:
    * Add and subtract days, weeks, months, years, decades, centuries, and even millennia to/from a date.
    * Increase or decrease a date by a specific number of days, weeks, months, or years.
    * Calculate the difference in days between two dates.
    * Get the current date.

* Date Validation & Comparison:
    * Check if a date is valid (e.g., checking leap years, valid days for specific months).
    * Compare two dates to check if one is before, after, or equal to the other.
    * Determine if a date is a weekday, weekend, or business day.
    * Check if a date is the last day of a month or the end of the week.

* Date Information:
    * Get the name of the weekday or month (short name).
    * Get the number of days, hours, minutes, or seconds in a year or month.
    * Get the day of the week for a specific date.
    * Retrieve the number of days remaining until the end of the week, month, or year.

* Date Formatting:
    * Convert a Date object to a string format (e.g., "dd/mm/yyyy").
    * Format dates in a custom string format.

* Special Date Calculations:
    * Calculate age in days based on birthdate.
    * Calculate vacation days between two dates.
    * Calculate the return date after a specified number of vacation days.

* Utilities:
    * Print week days or a calendar for a specific month or year.

## Example Usage
\#include "Date.h"

int main() 
{
    Date today; // Current date
    Date specificDate("07/01/2025");  // Specific date from string

    today.print();  // Output current date in "dd/mm/yyyy" format

    // Manipulating the date
    Date nextWeek = Date::increaseDateByOneWeek(today);
    nextWeek.print();

    // Comparing dates
    bool isBefore = today.isDateBeforeDate2(specificDate);
    cout << "Is today before 07/01/2025? " << (isBefore ? "Yes" : "No") << endl;
    
    // Calculate age in days
    Date birthDate("01/01/2000");
    cout << "Age in days: " << birthDate.caluclateMyAgeInDays() << endl;
}
## Methods Overview
* getDay(), getMonth(), getYear(): Get the respective components of the date.
* setDay(), setMonth(), setYear(): Set the respective components of the date.
* addDaysToDate(), increaseDateByXDays(): Add days to the date.
* getDifferenceInDays(): Get the difference in days between two dates.
* isDateBeforeDate2(), isDateAfterDate2(), isDateEqualToDate2(): Compare two dates.
* daysUntilTheEndOfWeek(), daysUntilTheEndOfMonth(), daysUntilTheEndOfYear(): Get the number of days left until the end of the week, month, or year.
* isLeapYear(), isValidDate(): Check leap years and validate the date.
## Installation
To use this library, simply include the Date.h header file in your project and link it with your C++ code.
