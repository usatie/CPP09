#include "BitcoinExchange.hpp"

// Exception
BitcoinExchange::Exception::Exception(const std::string& msg) : _msg(msg) {}
BitcoinExchange::Exception::Exception(const BitcoinExchange::Exception& b)
    : _msg(b._msg) {}
BitcoinExchange::Exception& BitcoinExchange::Exception::operator=(
    const Exception& b) {
  if (this != &b) {
    _msg = b._msg;
  }
  return *this;
}
BitcoinExchange::Exception::~Exception() {}
const std::string& BitcoinExchange::Exception::what() const { return _msg; }
