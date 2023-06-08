#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>

class RPN {
 public:
  RPN();
  RPN(const RPN& r);
  RPN& operator=(const RPN& r);
  ~RPN();
  // Member functions
  void push(char c);
  int top() const;
  size_t size() const;

 private:
  std::stack<int> _numberStack;
  static bool isOperator(char c);
};

#endif
