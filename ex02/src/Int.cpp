#include "Int.hpp"

long Int::comp_count = 0;

Int::Int(int data) : data(data) {}
Int::Int(const Int& i) : data(i.data) {}
Int& Int::operator=(const Int& i) {
  data = i.data;
  return *this;
}
Int::~Int() {}

bool Int::operator<(const Int& rhs) const {
  comp_count++;
  return data < rhs.data;
}

bool Int::operator>(const Int& rhs) const {
  comp_count++;
  return data > rhs.data;
}

std::ostream& operator<<(std::ostream& os, const Int& i) {
  os << i.data;
  return os;
}
