#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
 public:
  // Orthodox Canonical Form
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& b);
  BitcoinExchange& operator=(const BitcoinExchange& b);
  ~BitcoinExchange();
  // Constructor
  BitcoinExchange(const std::string& filename);
  // Getter
  const std::map<std::string, double>& getPrices() const;
  // Exception
  class Exception: public std::exception {
   public:
    Exception(const std::string& msg);
    Exception(const Exception& b);
    Exception& operator=(const Exception& b);
    ~Exception() throw();
    const char *what() const throw() ;
   private:
    std::string _msg;
  };
  // Member functions
  double getRate(const std::string &date) const;
 public:
  // Static functions
  static void validateDate(const std::string& date) throw(BitcoinExchange::Exception);
  static double stringToDouble(const std::string& rate) throw(BitcoinExchange::Exception);
 private:
  // Data
  std::map<std::string, double> _rates;
};

std::ostream& operator<<(std::ostream& os, const BitcoinExchange& b);

#endif
