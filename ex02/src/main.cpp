#include <iomanip>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "PMergeMe.hpp"

template <typename Container>
void print(Container& container) {
  std::cout << "{" ;
  for (typename Container::iterator it = container.begin() ; it != container.end() ; ++it) {
    std::cout << " " << *it ;
  }
  std::cout << "}" ;
  std::cout << std::endl ;
}

int main(int argc, char* argv[]) {
  (void)argc, (void)argv ;
  /*
  std::vector<int> orig(100) ;
  std::iota(orig.begin(), orig.end(), 0) ;
  std::random_shuffle(orig.begin(), orig.end()) ;
  */
  /*
  std::vector<int> orig ;
  for (int i = 0; i < 100; ++i) {
    orig.push_back(rand() % 100) ;
  }
  */

  int sizes[] = { 0, 1, 2, 4, 8, 100, 1000, 10000 } ;
  for (size_t i = 0 ; i < sizeof(sizes) / sizeof(sizes[0]) ; ++i) {
    std::vector<int> orig(sizes[i]) ;
    std::iota(orig.begin(), orig.end(), 0) ;
    std::random_shuffle(orig.begin(), orig.end()) ;
    std::cout << "size(" << sizes[i] << ") " << std::endl ;
    // Sort vector
    {
      std::cout << "Sort vector" << std::endl ;
      std::vector<int> v(orig) ;
      PMergeMe::merge_insert_sort(v) ;
      std::cout << "  is_sorted: " << std::boolalpha << std::is_sorted(v.begin(), v.end()) << std::endl ;
    }

    // Sort list
    {
      std::cout << "Sort list" << std::endl ;
      std::list<int> l(orig.begin(), orig.end()) ;
      PMergeMe::merge_insert_sort(l) ;
      std::cout << "  is_sorted: " << std::boolalpha << std::is_sorted(l.begin(), l.end()) << std::endl ;
    }
    std::cout << std::endl ;
  }
  return 0;
}
