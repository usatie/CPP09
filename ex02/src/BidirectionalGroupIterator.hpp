#ifndef BIDIRECTIONALGROUPITERATOR_HPP
#define BIDIRECTIONALGROUPITERATOR_HPP

#include <iterator>

// This function assumes lhs is always greater than rhs
template <typename Iterator>
size_t diff(const Iterator& lhs, const Iterator& rhs) {
  ssize_t diff = 0 ;
  Iterator it = rhs ;
  while (it != lhs) {
    ++diff ;
    ++it ;
  }
  return diff ;
}

// it + increment <= end
template <typename Iterator>
bool lte_end(Iterator it, size_t increment, Iterator end) {
  while (increment > 0) {
    if (it == end) return false ;
    ++it ;
    --increment ;
  }
  return true ;
}

template <typename Iterator>
class BidirectionalGroupIterator {
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
    BidirectionalGroupIterator() {}
    BidirectionalGroupIterator(Iterator it, difference_type size) : _it(it), _size(size) {}

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
    reference operator*() const {
      return *std::next(_it, _size - 1) ;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Increment/decrement operators
    BidirectionalGroupIterator& operator++() { std::advance(_it, _size) ; return *this ; }
    BidirectionalGroupIterator& operator--() { std::advance(_it, -_size) ; return *this ; }
    //BidirectionalGroupIterator& operator+=(difference_type increment) { _it += increment*_size ; return *this ; }
    //BidirectionalGroupIterator& operator-=(difference_type increment) { _it -= increment*_size ; return *this ; }
    BidirectionalGroupIterator& operator+=(difference_type increment) { std::advance(_it, increment*_size) ; return *this ; }
    BidirectionalGroupIterator& operator-=(difference_type increment) { std::advance(_it, -increment*_size) ; return *this ; }

    ////////////////////////////////////////////////////////////////////////////
    // Element Access operators

    ////////////////////////////////////////////////////////////////////////////
    // Comparison operators
    friend bool operator==(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) { return lhs.base() == rhs.base() ; }
    friend bool operator!=(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) { return lhs.base() != rhs.base() ; }
    ////////////////////////////////////////////////////////////////////////////
    // Relational operators
    friend bool operator<(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) { return lhs.base() < rhs.base() ; }
    friend bool operator>(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) { return lhs.base() > rhs.base() ; }
    friend bool operator<=(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) { return lhs.base() == rhs.base() || lhs.base() < rhs.base() ; }
    friend bool operator>=(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) { return lhs.base() >= rhs.base() ; }
    ////////////////////////////////////////////////////////////////////////////
    // Arithmetic operators
    friend BidirectionalGroupIterator operator+(BidirectionalGroupIterator it, difference_type size) {
      it += size ;
      return it ;
    }
    friend BidirectionalGroupIterator operator+(difference_type size, BidirectionalGroupIterator it) {
      it += size ;
      return it ;
    }
    friend BidirectionalGroupIterator operator-(BidirectionalGroupIterator it, difference_type size) {
      it -= size ;
      return it ;
    }
    friend difference_type operator-(const BidirectionalGroupIterator& lhs, const BidirectionalGroupIterator& rhs) {
      return diff(lhs.base(), rhs.base()) / lhs.size() ;
      //return (lhs.base() - rhs.base()) / lhs.size() ;
    }
    ////////////////////////////////////////////////////////////////////////////
    // iter_swap
    friend void iter_swap(BidirectionalGroupIterator lhs, BidirectionalGroupIterator rhs) {
      std::swap_ranges(lhs.base(), std::next(lhs.base(), lhs.size()), rhs.base()) ;
    }
    ////////////////////////////////////////////////////////////////////////////
    // less
    static bool less(const BidirectionalGroupIterator &lhs, const BidirectionalGroupIterator &rhs) {
      return *lhs < *rhs ;
    }
};

//////////////////////////////////////////////////////////////////////////////
// Construction functions
template <typename Iterator>
BidirectionalGroupIterator<Iterator> make_bidirectional_group_iterator(Iterator it, typename BidirectionalGroupIterator<Iterator>::difference_type size) {
  return BidirectionalGroupIterator<Iterator>(it, size) ;
}

template <typename Iterator>
BidirectionalGroupIterator<Iterator> make_bidirectional_group_iterator(BidirectionalGroupIterator<Iterator> it, typename BidirectionalGroupIterator<Iterator>::difference_type size) {
  size *= it.size() ;
  return BidirectionalGroupIterator<Iterator>(it.base(), size) ;
}

template <typename Iterator>
std::ostream& operator<<(std::ostream& os, const BidirectionalGroupIterator<Iterator>& it) {
  os << "[" << *it << "]" ;
  return os ;
}
#endif
