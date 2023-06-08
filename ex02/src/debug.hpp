#ifndef DEBUG_HPP
#define DEBUG_HPP

template <typename Iterator>
void print_pairs(RandomAccessGroupIterator<Iterator> first, RandomAccessGroupIterator<Iterator> last) {
  for (RandomAccessGroupIterator<Iterator> it = first ; it != last ; it += 2) {
    std::cout << " " << *it << " " << *(it + 1) << std::endl ;
  }
}

template <typename Iterator>
void print_pairs(BidirectionalGroupIterator<Iterator> first, BidirectionalGroupIterator<Iterator> last) {
  for (BidirectionalGroupIterator<Iterator> it = first ; it != last ; it += 2) {
    std::cout << " " << *it << " " << *(it + 1) << std::endl ;
  }
}

template <typename Container>
void print_container(Container& container) {
  std::cout << "{" ;
  for (typename Container::iterator it = container.begin() ; it != container.end() ; ++it) {
    std::cout << " " << *it ;
  }
  std::cout << "}" ;
  std::cout << std::endl ;
}

#endif
