#include <iomanip>
#include <iostream>
#include "RPN.hpp"

static int run(char* exp) ;

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl ;
    return 1 ;
  }
  return run(argv[1]) ;
}

static int run(char *exp) {
  RPN rpn ;
  while (*exp) {
    if (*exp == ' ') {
      exp++ ;
      continue ;
    }
    try {
      rpn.push(*exp++) ;
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl ;
      return 1;
    }
  }
  // The stack should not be empty
  if (rpn.size() == 0) {
    std::cerr << "Error: Empty expression" << std::endl ;
    return 1 ;
  }
  // The stack should have only one element at the end
  if (rpn.size() != 1) {
    std::cerr << "Error: Extra operands or insufficient operators" << std::endl ;
    return 1 ;
  }
  // Print the result
  std::cout << rpn.top() << std::endl ;
  return 0 ;
}
