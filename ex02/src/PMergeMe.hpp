#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <vector>

#include "BidirectionalGroupIterator.hpp"
#include "RandomAccessGroupIterator.hpp"

class PMergeMe {
 public:
  PMergeMe();
  PMergeMe(const PMergeMe& p);
  PMergeMe& operator=(const PMergeMe& p);
  ~PMergeMe();

  template <typename T>
  static void merge_insert_sort(std::vector<T>& v) {
    sort_impl(make_random_access_group_iterator(v.begin(), 1),
              make_random_access_group_iterator(v.end(), 1));
  }
  template <typename T>
  static void merge_insert_sort(std::list<T>& v) {
    sort_impl(make_bidirectional_group_iterator(v.begin(), 1),
              make_bidirectional_group_iterator(v.end(), 1));
  }

 protected:
 private:
  template <typename Iterator>
  static void sort_impl(RandomAccessGroupIterator<Iterator> first,
                        RandomAccessGroupIterator<Iterator> last);
  template <typename Iterator>
  static void sort_impl(BidirectionalGroupIterator<Iterator> first,
                        BidirectionalGroupIterator<Iterator> last);
};

#include "bidirectional_sort_impl.tpp"
#include "random_access_sort_impl.tpp"

#endif
