#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <numeric>

#include "PMergeMe.hpp"
#include "Int.hpp"

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define CLOCKS_PER_US (CLOCKS_PER_SEC / 1000000)

// Print a vector
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end();
       ++it) {
    os << " " << *it;
  }
  return os;
}

void print_elapsed(std::clock_t elapsed) {
  double elapsed_secs = static_cast<double>(elapsed) / CLOCKS_PER_SEC;
  double elapsed_ms = static_cast<double>(elapsed) / CLOCKS_PER_MS;
  double elapsed_us = static_cast<double>(elapsed) / CLOCKS_PER_US;
  if (elapsed > CLOCKS_PER_SEC) {
    std::cout << std::setw(8) << elapsed_secs << " s" << std::endl;
  } else if (elapsed > CLOCKS_PER_MS) {
    std::cout << std::setw(8) << elapsed_ms << " ms" << std::endl;
  } else {
    std::cout << std::setw(8) << elapsed_us << " us" << std::endl;
  }
}

// Test the sort function
template <typename T>
void test_sort(std::vector<T>& orig) {
  std::cout << "Before: " << orig << std::endl;
  {
    std::vector<T> v(orig);
    std::vector<T> v2(orig);
    std::list<T> l(orig.begin(), orig.end());

    std::clock_t elapsed_vec, elapsed_list;
#if BENCH
    std::clock_t elapsed_std_sort;
    long comp_count_fjmi, comp_count_std_sort;
#endif
    // Sort Vector with Ford-Johnson Algorithm
    {
      Int::comp_count = 0;
      std::clock_t start = std::clock();  // Start the clock
      PMergeMe::merge_insert_sort(v);
      std::clock_t end = std::clock();  // Stop the clock
#if BENCH
      comp_count_fjmi = Int::comp_count;
#endif
      elapsed_vec = end - start;
    }
    // Sort List with Ford-Johnson Algorithm
    {
      std::clock_t start = std::clock();  // Start the clock
      PMergeMe::merge_insert_sort(l);
      std::clock_t end = std::clock();  // Stop the clock
      elapsed_list = end - start;
    }
    // Sort Vector with std::sort
#if BENCH
    {
      Int::comp_count = 0;
      std::clock_t start = std::clock();  // Start the clock
      std::sort(v2.begin(), v2.end());
      std::clock_t end = std::clock();  // Stop the clock
      comp_count_std_sort = Int::comp_count;
      elapsed_std_sort = end - start;
    }
#endif
    std::cout << "After:  " << v << std::endl;
    std::cout << "Time to process a range of " << std::setw(8) << v.size()
              << " elements with std::vector : " ;
    print_elapsed(elapsed_vec);
    std::cout << "Time to process a range of " << std::setw(8) << v.size()
              << " elements with std::list   : " ;
    print_elapsed(elapsed_list);
#if BENCH
    std::cout << "Time to process a range of " << std::setw(8) << v.size()
              << " elements with std::sort   : " ;
    print_elapsed(elapsed_std_sort);
    std::cout << "Number of comparisons with Ford-Johnson Algorithm : "
              << std::setw(8) << comp_count_fjmi << std::endl;
    std::cout << "Number of comparisons with std::sort              : "
              << std::setw(8) << comp_count_std_sort << std::endl;
#endif
#if DEBUG
    std::cout << "vector is_sorted: " << std::boolalpha
              << std::is_sorted(v.begin(), v.end()) << std::endl;
    std::cout << "list   is_sorted: " << std::boolalpha
              << std::is_sorted(l.begin(), l.end()) << std::endl;
#endif
  }
  std::cout << std::endl;
}

int stringToDouble(const std::string& str) throw(std::exception) {
  if (str.empty()) {
    throw std::runtime_error("Invalid string(empty)");
  }
  char* endptr;
  errno = 0;
  long value = std::strtol(str.c_str(), &endptr, 10);
  if (*endptr != '\0') {
    throw std::runtime_error("Invalid string " + str);
  }
  if (errno == ERANGE) {
    throw std::runtime_error("Invalid string(overflow) " + str);
  }
  if (value > std::numeric_limits<int>::max()) {
    throw std::runtime_error("Invalid string(overflow) " + str);
  }
  if (value < 0) {
    throw std::runtime_error("Invalid string(negative) " + str);
  }
  return value;
}

int main(int argc, char* argv[]) {
  std::vector<Int> orig;
  for (int i = 1; i < argc; ++i) {
    try {
      orig.push_back(Int(stringToDouble(argv[i])));
    } catch (std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }
  }
  test_sort(orig);

  /*
  int sizes[] = { 0, 1, 2, 4, 8, 100, 1000, 10000 } ;
  for (size_t i = 0 ; i < sizeof(sizes) / sizeof(sizes[0]) ; ++i) {
    std::vector<int> orig(sizes[i]) ;
    std::iota(orig.begin(), orig.end(), 0) ;
    std::random_shuffle(orig.begin(), orig.end()) ;
  //std::vector<int> orig(100) ;
  //std::iota(orig.begin(), orig.end(), 0) ;
  //std::random_shuffle(orig.begin(), orig.end()) ;
  //std::vector<int> orig ;
  //for (int i = 0; i < 100; ++i) {
  //  orig.push_back(rand() % 100) ;
  //}
    std::cout << "size(" << sizes[i] << ") " << std::endl ;
    test_sort(orig) ;
  }
  */
  return 0;
}
