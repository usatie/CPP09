#ifndef DATE_HPP
#define DATE_HPP

#include <string>

class Date {
 public:
  // Orthodox Canonical Form
  Date();
  Date(const Date& d);
  Date& operator=(const Date& d);
  ~Date();
  // Constructor
  explicit Date(const std::string& date) throw(Date::Exception);
  Date(int y, int m, int d) throw(Date::Exception);
  // Comparison operators
  bool operator<(const Date& d) const;
  bool operator>(const Date& d) const;
  bool operator==(const Date& d) const;
  bool operator!=(const Date& d) const;
  bool operator<=(const Date& d) const;
  bool operator>=(const Date& d) const;
  // Exception
  class Exception : public std::exception {
   public:
    explicit Exception(const std::string& msg);
    Exception(const Exception& e);
    Exception& operator=(const Exception& e);
    ~Exception() throw();
    const char* what() const throw();

   private:
    std::string _msg;
  };

 private:
  // helper functions
  void validate() const throw(Date::Exception);
  bool isLeapYear() const;
  int daysInMonth() const;

 public:
  int year;
  int month;
  int day;
};

#endif
