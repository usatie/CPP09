#include "PMergeMe.hpp"
#include <iostream>

PMergeMe::PMergeMe() {}

PMergeMe::PMergeMe(const PMergeMe& p) {}

PMergeMe& PMergeMe::operator =(const PMergeMe& p) {
  if (this != &p) {
    // copy data
  }
	return *this ;
}

PMergeMe::~PMergeMe() {
	std::cout << "[ PMergeMe destructor called ]" << std::endl ;
}
