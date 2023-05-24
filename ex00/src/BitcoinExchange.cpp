#include "BitcoinExchange.hpp"
#include "Date.hpp"

#include <fstream>
#include <iostream>

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
    // Parse line
    std::string::size_type pos = line.find(',');
    if (pos == std::string::npos) {
      throw Exception("Could not parse line " + line);
    }
    std::string date = line.substr(0, pos);
    std::string rate = line.substr(pos + 1);
    // Validate date
    validateDate(date);
    // check duplicate
    if (_rates.find(date) != _rates.end()) {
      throw Exception("Duplicate date " + date);
    }
    // Validate rate
    _rates[date] = stringToDouble(rate);
    // check negative rate
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

// Rate Getter
double BitcoinExchange::getRate(const std::string& date) const {
  std::map<std::string, double>::const_iterator it = _rates.upper_bound(date);
  if (it == _rates.begin()) {
    throw Exception("Invalid date " + date);
  }
  --it ;
  return it->second;
}

// Date Validation
void BitcoinExchange::validateDate(std::string const& date) throw(BitcoinExchange::Exception) {
  try {
    Date d(date);
  } catch (Date::Exception& e) {
    throw Exception(e.what());
  }
}

// Rate Validation
double BitcoinExchange::stringToDouble(const std::string& str) throw(BitcoinExchange::Exception) {
  if (str.empty()) {
    throw Exception("Invalid string(empty)");
  }
  char *endptr;
  errno = 0 ;
  double value = std::strtod(str.c_str(), &endptr);
  if (*endptr != '\0') {
    throw Exception("Invalid string " + str);
  }
  if ( errno == ERANGE ) {
    throw Exception("Invalid string(overflow) " + str);
  }
  return value;
}
