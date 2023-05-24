#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>

#include "BitcoinExchange.hpp"

void run(const BitcoinExchange &exchange, std::ifstream &file ) ;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }
  // read input file
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cout << "Could not open file " << argv[1] << std::endl;
    return 1;
  }
  // 
  try {
    BitcoinExchange exchange("data.csv");
    run(exchange, file);
  } catch (const BitcoinExchange::Exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

void parseLine(const std::string &line, std::string &date, float &value) {
  std::string::size_type pos = line.find(" | ");
  if (pos == std::string::npos) {
    throw BitcoinExchange::Exception("Could not parse line " + line);
  }
  // Parse date
  date = line.substr(0, pos);
  BitcoinExchange::validateDate(date);
  // parse value
  std::string valueString = line.substr(pos + 3);
  value = BitcoinExchange::stringToDouble(valueString);
  if (value < 0 || value > 1000) {
    throw BitcoinExchange::Exception("Value must be within [0, 1000]: " + valueString);
  }
}

void run(const BitcoinExchange &exchange, std::ifstream &file ) {
  (void)exchange;
  std::string line ;
  while (std::getline(file, line)) {
    std::string date;
    float value;
    try {
      parseLine(line, date, value);
      std::cout << date << " " << value << std::endl;
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      continue;
    }
  }
  file.close();
}
