#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <numeric>

#include "PMergeMe.hpp"

class Int {
 public:
  static long comp_count;
  int data;
  explicit Int(int data) : data(data) {}
  bool operator<(const Int& rhs) const {
    comp_count++;
    return data < rhs.data;
  }
  bool operator>(const Int& rhs) const {
    comp_count++;
    return data > rhs.data;
  }
};

long Int::comp_count = 0;

std::ostream& operator<<(std::ostream& os, const Int& i) {
  os << i.data;
  return os;
}

template <typename Container>
void print(Container& container) {
  std::cout << "{";
  for (typename Container::iterator it = container.begin();
       it != container.end(); ++it) {
    std::cout << " " << *it;
  }
  std::cout << "}";
  std::cout << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end();
       ++it) {
    os << " " << *it;
  }
  return os;
}

template <typename T>
void test_sort(std::vector<T>& orig) {
  std::cout << "Before: " << orig << std::endl;
  // Sort vector
  {
    std::vector<T> v(orig);
    std::vector<T> v2(orig);
    std::list<T> l(orig.begin(), orig.end());

    double elapsed_secs_vector, elapsed_secs_list, elapsed_secs_std_sort;
    long comp_count_fjmi, comp_count_std_sort;
    {
      Int::comp_count = 0;
      std::clock_t start = std::clock();  // Start the clock
      PMergeMe::merge_insert_sort(v);
      std::clock_t end = std::clock();  // Stop the clock
      comp_count_fjmi = Int::comp_count;
      elapsed_secs_vector = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    }
    {
      std::clock_t start = std::clock();  // Start the clock
      PMergeMe::merge_insert_sort(l);
      std::clock_t end = std::clock();  // Stop the clock
      elapsed_secs_list = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    }
    {
      Int::comp_count = 0;
      std::clock_t start = std::clock();  // Start the clock
      std::sort(v2.begin(), v2.end());
      std::clock_t end = std::clock();  // Stop the clock
      comp_count_std_sort = Int::comp_count;
      elapsed_secs_std_sort = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    }
    std::cout << "After:  " << v << std::endl;
    std::cout << "Time to process a range of " << std::setw(8) << v.size()
              << " elements with std::vector : " << std::setw(8)
              << elapsed_secs_vector << " s" << std::endl;
    std::cout << "Time to process a range of " << std::setw(8) << v.size()
              << " elements with std::list   : " << std::setw(8)
              << elapsed_secs_list << " s" << std::endl;
    std::cout << "Time to process a range of " << std::setw(8) << v.size()
              << " elements with std::sort   : " << std::setw(8)
              << elapsed_secs_std_sort << " s" << std::endl;
    std::cout << "Number of comparisons with Ford-Johnson Algorithm : "
              << std::setw(8) << comp_count_fjmi << std::endl;
    std::cout << "Number of comparisons with std::sort              : "
              << std::setw(8) << comp_count_std_sort << std::endl;
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
