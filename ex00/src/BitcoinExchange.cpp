#include "BitcoinExchange.hpp"

#include <fstream>
#include <iostream>

static bool isValidDate(std::string const& date) ;

// Orthodox Canonical Form
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& b) : _rates(b._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& b) {
  if (this != &b) {
    _rates = b._rates;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Constructor
BitcoinExchange::BitcoinExchange(const std::string& filename) {
  // read file
  std::cout << "Reading file " << filename << std::endl;
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    throw Exception("Could not open file " + filename);
  }
  // parse
  std::string line;
  // parse header
  if (!std::getline(file, line)) {
    throw BitcoinExchange::Exception("Could not read header");
  }
  if (line != "date,exchange_rate") {
    throw BitcoinExchange::Exception("Invalid header");
  }
  // parse data
  while (std::getline(file, line)) {
    std::string::size_type pos = line.find(',');
    if (pos == std::string::npos) {
      throw Exception("Could not parse line " + line);
    }
    std::string date = line.substr(0, pos);
    if (!isValidDate(date)) {
      throw Exception("Invalid date " + date);
    }
    std::string rate = line.substr(pos + 1);
    if (rate.empty()) {
      throw Exception("Invalid rate(empty)");
    }
    char *endptr;
    errno = 0 ;
    _rates[date] = std::strtod(rate.c_str(), &endptr);
    if (*endptr != '\0') {
      throw Exception("Invalid rate " + rate);
    }
    if ( errno == ERANGE ) {
      throw Exception("Invalid rate(overflow) " + rate);
    }
    if (_rates[date] < 0) {
      throw Exception("Invalid rate(negative) " + rate);
    }
  }
  file.close();
}

// Getter
const std::map<std::string, double>& BitcoinExchange::getPrices() const {
  return _rates;
}
std::ostream& operator<<(std::ostream& os, const BitcoinExchange& b) {
  for (std::map<std::string, double>::const_iterator it = b.getPrices().begin();
       it != b.getPrices().end(); ++it) {
    os << it->first << ": " << it->second << std::endl;
  }
  return os;
}

// Date Validation
static bool isDigit(std::string const& number) {
  for (std::string::size_type i = 0; i < number.size(); ++i) {
    if (!std::isdigit(number[i])) {
      return false;
    }
  }
  return true;
}

static bool isLeapYear(int year) {
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

static int daysInMonth(int year, int month) {
  if (month == 2) {
    if (isLeapYear(year)) {
      return 29;
    }
    return 28;
  }
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    return 30;
  }
  return 31;
}

// A valid date will always be in the following format: Year-Month-Day
// For example: 2014-01-01
static bool isValidDate(std::string const& date) {
  // Check if date is in the format Year-Month-Day
  if (date.size() != 10) {
    return false;
  }
  if (date[4] != '-' || date[7] != '-') {
    return false;
  }
  // Extract year, month and day
  std::string year = date.substr(0, 4);
  std::string month = date.substr(5, 2);
  std::string day = date.substr(8, 2);
  // Check if year, month and day are digits
  if (!isDigit(year) || !isDigit(month) || !isDigit(day)) {
    return false;
  }
  // No error checking for atoi here, because we already checked the strings
  int y = std::atoi(year.c_str());
  int m = std::atoi(month.c_str());
  int d = std::atoi(day.c_str());
  // Check if month is valid
  if (m < 1 || m > 12) {
    return false;
  }
  // Check if day is valid
  if (d < 1 || d > daysInMonth(y, m)) {
    return false;
  }
  // Bitcoin exchange rate data starts on 2009-01-03
  if (y < 2009 || (y == 2009 && m == 1 && d < 3)) {
    return false;
  }
  return true;
}

