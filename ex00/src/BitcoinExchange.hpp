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
  class Exception {
   public:
    Exception(const std::string& msg);
    Exception(const Exception& b);
    Exception& operator=(const Exception& b);
    ~Exception();
    const std::string& what() const;
   private:
    std::string _msg;
  };
 protected:
 private:
  // Data
  std::map<std::string, double> _rates;
};

std::ostream& operator<<(std::ostream& os, const BitcoinExchange& b);

#endif
