#include <iomanip>
#include <iostream>
#include <map>

#include "BitcoinExchange.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }
  try {
    BitcoinExchange exchange("data.csv");
    std::cout << exchange;
  } catch (const BitcoinExchange::Exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
