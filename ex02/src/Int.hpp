#ifndef INT_HPP
#define INT_HPP

#include <iostream>

class Int {
  public:
    // Orthodox Canonical Form
    Int() ;
    Int(const Int& i) ;
    Int& operator=(const Int& i) ;
    ~Int() ;

 public:
  static long comp_count;
  int data;
  explicit Int(int data) ;
  bool operator<(const Int& rhs) const ;
  bool operator>(const Int& rhs) const ;
};

std::ostream& operator<<(std::ostream& os, const Int& i) ;

#endif
