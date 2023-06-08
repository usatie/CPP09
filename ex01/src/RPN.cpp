#include "RPN.hpp"

#include <iostream>

// Orthodox Canonical Form
RPN::RPN() {}

RPN::RPN(const RPN& r) : _numberStack(r._numberStack) {}

RPN& RPN::operator=(const RPN& r) {
  if (this != &r) {
    _numberStack = r._numberStack;
  }
  return *this;
}

RPN::~RPN() {}

// Member functions
bool RPN::isOperator(char c) {
  switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
      return true;
    default:
      return false;
  }
}
void RPN::push(char c) {
  if (isdigit(c)) {
    _numberStack.push(c - '0');
    return;
  } else if (isOperator(c)) {
    if (_numberStack.size() < 2) {
      throw std::runtime_error("Error: not enough operands");
    }
    int lhs = _numberStack.top();
    _numberStack.pop();
    int rhs = _numberStack.top();
    _numberStack.pop();
    if (c == '+') {
      _numberStack.push(rhs + lhs);
    } else if (c == '-') {
      _numberStack.push(rhs - lhs);
    } else if (c == '*') {
      _numberStack.push(rhs * lhs);
    } else if (c == '/') {
      if (lhs == 0) {
        throw std::runtime_error("Error: divide by zero");
      }
      _numberStack.push(rhs / lhs);
    }
    return;
  } else {
    throw std::runtime_error("Error: invalid character");
  }
}

int RPN::top() const {
  if (_numberStack.empty()) {
    throw std::runtime_error("Error: stack is empty");
  }
  return _numberStack.top();
}
size_t RPN::size() const { return _numberStack.size(); }
