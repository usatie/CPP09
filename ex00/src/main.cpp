#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

#include "BitcoinExchange.hpp"
#include "Date.hpp"

void run(const BitcoinExchange &exchange, std::ifstream &file);

int main(int argc, char *argv[]) {
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
  } catch (const BitcoinExchange::Exception &e) {
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
  try {
    Date d(date);
  } catch (const Date::Exception &e) {
    throw BitcoinExchange::Exception(e.what());
  }
  // parse value
  std::string valueString = line.substr(pos + 3);
  value = BitcoinExchange::stringToDouble(valueString);
  if (value < 0 || value > 1000) {
    throw BitcoinExchange::Exception("Value must be within [0, 1000]: " +
                                     valueString);
  }
}

void run(const BitcoinExchange &exchange, std::ifstream &file) {
  std::string line;
  // parse header
  if (!std::getline(file, line)) {
    throw BitcoinExchange::Exception("Could not read header");
  }
  if (line != "date | value") {
    throw BitcoinExchange::Exception("Invalid header");
  }
  // parse data
  while (std::getline(file, line)) {
    try {
      std::string date;
      float value;
      parseLine(line, date, value);
      double rate = exchange.getRate(date);
      std::cout << date << " => " << rate * value << std::endl;
    } catch (const std::exception &e) {
      // limit line length to 80 characters
      if (line.size() > 80) {
        line.resize(80);
        line += "...";
      }
      std::cerr << "Error: " << e.what() << ": \"" << line << "\"" << std::endl;
      continue;
    }
  }
  file.close();
}
