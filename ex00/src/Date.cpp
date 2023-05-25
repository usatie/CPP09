#include "Date.hpp"

#include <iostream>

// Orthodox Canonical Form
Date::Date() : year(1970), month(1), day(1) {}

Date::Date(const Date& d) : year(d.year), month(d.month), day(d.day) {}

Date& Date::operator=(const Date& d) {
  if (this != &d) {
    year = d.year;
    month = d.month;
    day = d.day;
  }
  return *this;
}

Date::~Date() {}

// Constructor
void Date::validate() const throw(Date::Exception) {
  if (year < 0 || year > 9999) {
    throw Date::Exception("Invalid year " + std::to_string(year));
  }
  if (month < 1 || month > 12) {
    throw Date::Exception("Invalid month " + std::to_string(month));
  }
  if (day < 1 || day > 31) {
    throw Date::Exception("Invalid day " + std::to_string(day));
  }
  if (day > daysInMonth()) {
    throw Date::Exception("Invalid day " + std::to_string(day));
  }
}

Date::Date(int y, int m, int d) throw(Date::Exception)
    : year(y), month(m), day(d) {
  validate();
}

static bool isDigit(std::string const& number) {
  for (std::string::size_type i = 0; i < number.size(); ++i) {
    if (!std::isdigit(number[i])) {
      return false;
    }
  }
  return true;
}

// A valid date will always be in the following format: Year-Month-Day
// For example: 2014-01-01
Date::Date(const std::string& date) throw(Date::Exception) {
  // Check if date is in the format Year-Month-Day
  if (date.size() != 10) {
    throw Date::Exception("Invalid date format: " + date);
  }
  if (date[4] != '-' || date[7] != '-') {
    throw Date::Exception("Invalid date format: " + date);
  }
  // Extract year, month and day
  std::string y = date.substr(0, 4);
  std::string m = date.substr(5, 2);
  std::string d = date.substr(8, 2);
  // Check if year, month and day are digits
  if (!isDigit(y) || !isDigit(m) || !isDigit(d)) {
    throw Date::Exception("Invalid date format: " + date);
  }
  // No error checking for atoi here, because we already checked the strings
  year = std::atoi(y.c_str());
  month = std::atoi(m.c_str());
  day = std::atoi(d.c_str());
  validate();
}

// helper functions
bool Date::isLeapYear() const {
  if (year % 4 != 0) {
    return false;
  }
  if (year % 100 != 0) {
    return true;
  }
  if (year % 400 != 0) {
    return false;
  }
  return true;
}

int Date::daysInMonth() const {
  switch (month) {
    case 2:
      return isLeapYear() ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    default:
      return 31;
  }
}

// Exception
Date::Exception::Exception(const std::string& msg) : _msg(msg) {}

Date::Exception::Exception(const Date::Exception& e) : _msg(e._msg) {}

Date::Exception& Date::Exception::operator=(const Date::Exception& e) {
  if (this != &e) {
    _msg = e._msg;
  }
  return *this;
}

Date::Exception::~Exception() throw() {}

const char* Date::Exception::what() const throw() { return _msg.c_str(); }

// Comparison operators
bool Date::operator<(const Date& d) const {
  return (year < d.year) || (year == d.year && month < d.month) ||
         (year == d.year && month == d.month && day < d.day);
}

// implement using less than operator
bool Date::operator>(const Date& d) const { return d < *this; }

bool Date::operator!=(const Date& d) const {
  return (*this < d) || (d < *this);
}

bool Date::operator==(const Date& d) const {
  return !(*this < d) && (d < *this);
}

bool Date::operator<=(const Date& d) const { return !(d < *this); }

bool Date::operator>=(const Date& d) const { return !(*this < d); }
