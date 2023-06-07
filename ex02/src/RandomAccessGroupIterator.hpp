#ifndef RANDOMACCESSGROUPITERATOR_HPP
#define RANDOMACCESSGROUPITERATOR_HPP
#include <iterator>
#include <iostream>

template <typename Iterator>
class RandomAccessGroupIterator {
  public:
    typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
    typedef Iterator iterator_type;
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    typedef typename std::iterator_traits<Iterator>::pointer pointer;
    typedef typename std::iterator_traits<Iterator>::reference reference;
  private:
    Iterator _it ;
    difference_type _size ;
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    RandomAccessGroupIterator() {}
    RandomAccessGroupIterator(Iterator it, difference_type size) : _it(it), _size(size) {}

    ////////////////////////////////////////////////////////////////////////////
    // Member access
    Iterator base() const { return _it ; }
    difference_type size() const { return _size ; }

    ////////////////////////////////////////////////////////////////////////////
    // Element access
    // This accesses the last element in the group
    // container   : {5, 3, 2, 1, 7, 6, 10, 8}
    // _it         : points to 5
    // _size       : 4
    // operator*() : 1
    reference operator*() const { return *std::next(_it, _size - 1) ; }

    ////////////////////////////////////////////////////////////////////////////
    // Increment/decrement operators
    RandomAccessGroupIterator& operator++() { std::advance(_it, _size) ; return *this ; }
    RandomAccessGroupIterator& operator+=(difference_type increment) { _it += increment*_size ; return *this ; }

    ////////////////////////////////////////////////////////////////////////////
    // Element Access operators

    ////////////////////////////////////////////////////////////////////////////
    // Comparison operators
    friend bool operator!=(const RandomAccessGroupIterator& lhs, const RandomAccessGroupIterator& rhs) { return lhs.base() != rhs.base() ; }
    ////////////////////////////////////////////////////////////////////////////
    // Arithmetic operators
    // e.g.
    // it + 1
    friend RandomAccessGroupIterator operator+(RandomAccessGroupIterator it, difference_type size) {
      it += size ;
      return it ;
    }
    // e.g.
    // end_it - begin_it
    friend difference_type operator-(const RandomAccessGroupIterator& lhs, const RandomAccessGroupIterator& rhs) {
      return (lhs.base() - rhs.base()) / lhs.size() ;
    }
    ////////////////////////////////////////////////////////////////////////////
    // iter_swap
    friend void iter_swap(RandomAccessGroupIterator lhs, RandomAccessGroupIterator rhs) {
      std::swap_ranges(lhs.base(), std::next(lhs.base(), lhs.size()), rhs.base()) ;
    }
    //////////////////////////////////////////////////////////////////////////////
    // less
    static bool less(const RandomAccessGroupIterator &lhs, const RandomAccessGroupIterator &rhs) {
      return *lhs < *rhs ;
    }
};

//////////////////////////////////////////////////////////////////////////////
// Construction functions
template <typename Iterator>
RandomAccessGroupIterator<Iterator> make_random_access_group_iterator(Iterator it, typename RandomAccessGroupIterator<Iterator>::difference_type size) {
  return RandomAccessGroupIterator<Iterator>(it, size) ;
}

template <typename Iterator>
RandomAccessGroupIterator<Iterator> make_random_access_group_iterator(RandomAccessGroupIterator<Iterator> it, typename RandomAccessGroupIterator<Iterator>::difference_type size) {
  size *= it.size() ;
  return RandomAccessGroupIterator<Iterator>(it.base(), size) ;
}

template <typename Iterator>
std::ostream& operator<<(std::ostream& os, const RandomAccessGroupIterator<Iterator>& it) {
  os << "[" << *it << "]" ;
  return os ;
}

//////////////////////////////////////////////////////////////////////////////
// Debug
template <typename Iterator>
void print_group_iterator(RandomAccessGroupIterator<Iterator> first, RandomAccessGroupIterator<Iterator> last) {
  for (RandomAccessGroupIterator<Iterator> it = first ; it != last ; ++it) {
    std::cout << " " << *it ;
  }
  std::cout << std::endl ;
}
#endif
