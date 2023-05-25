#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>

class RPN {
public:
	RPN() ;
	RPN(const RPN& r) ;
	RPN& operator =(const RPN& r) ;
	~RPN() ;
  // Member functions
  void push(char c) ;
  int top() ;
  size_t size() ;
private:
  std::stack<int> _numberStack ;
  static bool isOperator(char c) ;
} ;

#endif
