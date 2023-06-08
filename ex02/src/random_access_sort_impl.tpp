#ifndef RANDOM_ACCESS_SORT_IMPL_TPP
#define RANDOM_ACCESS_SORT_IMPL_TPP

#include "PMergeMe.hpp"
////////////////////////////////////////////////////////////////////////////
// Ford Johnson Merge Insertion Sort
template <typename Iterator>
void PMergeMe::sort_impl(
    RandomAccessGroupIterator<Iterator> first,
    RandomAccessGroupIterator<Iterator> last
    )
  {
  typedef RandomAccessGroupIterator<Iterator> GroupIterator ;
  typedef typename GroupIterator::difference_type difference_type ;

  difference_type size = last - first ;

  // If size is 1, already sorted.
  if (size < 2) return ;

  // Whether there is a stray element not in a pair at the end of the chain.
  bool has_stray = (size % 2 != 0) ;

  //////////////////////////////////////////////////////////////////////////
  // Group elements by pairs
#if DEBUG
  std::cout 
    << "size(" << size << ") "
    << "Group elements by pairs" << std::endl ;
#endif
  GroupIterator end = has_stray ? std::prev(last) : last ;
  // print before swap
#if DEBUG
  std::cout << "before swap:" << std::endl ;
  print_pairs(first, end) ;
#endif

  // Swap if necessary (winner will be on the right)
  for (GroupIterator it = first ; it != end ; it += 2) {
    // Compare the two elements in the pair and swap them if they are out of order.
    if (*it > *(it + 1)) {
      iter_swap(it, it + 1) ;
    }
  }
  // print after swap
#if DEBUG
  std::cout << "after swap:" << std::endl ;
  print_pairs(first, end) ;
#endif

  //////////////////////////////////////////////////////////////////////////
  // Recursively sort the pairs by winner
#if DEBUG
  std::cout
    << "size(" << size << ") "
    << "Recursively sort the pairs by max" << std::endl ;
#endif
  sort_impl(make_random_access_group_iterator(first, 2), make_random_access_group_iterator(end, 2)) ;

  //////////////////////////////////////////////////////////////////////////
  // Separate main chain and pend elements
#if DEBUG
  std::cout
    << "size(" << size << ") "
    << "Separate main chain and pend elements" << std::endl ;
#endif
  typedef typename std::vector< GroupIterator > vector_t ;
  typedef typename std::pair<typename vector_t::difference_type, GroupIterator> pair_t ;
  typedef typename std::vector< pair_t > pair_vector_t ;
  typedef typename vector_t::iterator vector_iterator_t ;
  typedef typename pair_vector_t::iterator pair_vector_iterator_t ;
  // Winner is inserted to chain, loser is inserted to pend
  vector_t chain ;
  pair_vector_t pend ; // to be inserted later, range of binary search
  chain.push_back(first) ;            // first loser
  chain.push_back(std::next(first)) ; // first winner

  // Add the rest of the winners/losers
  for (GroupIterator it = first + 2 ; it != end ; it += 2) {
    // std::next(it) : Winner
    // `it`          : Loser
    // `tmp`         : Insertion point of the winner
    // Winner is inserted to chain, loser is inserted to pend
    // `tmp` is necessary when inserting loser to chain.
    // (Binary searching range between chain.begin() to `tmp`)
    vector_iterator_t tmp = chain.insert(chain.end(), std::next(it)) ;
    pend.push_back(pair_t(tmp - chain.begin(), it)) ;

    /*
     * THIS IS RANDOM ACCESS ITERATOR SPECIFIC 
     *                                         */
    // after insertion, this index may be invalidated.
    // That's why I use index instead of iterator for vector.
    // After each insertion, increment the indices of the elements after the
    // insertion point.
  }
  // Add the last element to pend if there is a stray element
  if (has_stray) {
    pend.push_back(pair_t(chain.end() - chain.begin(), end)) ;
  }
  // print chain and pend
#if DEBUG
  std::cout << "chain: " ;
  print_container(chain) ;
  std::cout << "pend: " << std::flush ;
  for (pair_vector_iterator_t pe = pend.begin() ; pe != pend.end() ; ++pe) {
    GroupIterator it = (*pe).second ;
    std::cout << " " << it << "(" << (*pe).first << ")";
  }
  std::cout << std::endl ;
#endif
  //////////////////////////////////////////////////////////////////////////
  // Binary insertion into the main chain
  //
  // At each cycle, we need to find the optimal pend element where to start
  // the insertion cycle again in a way that minimizes the number of
  // comparisions performed.
  //
  // The sums of sizes of every two adjacent groups form a sequence of powers
  // of two. Thus, the sizes of groups are: 2, 2, 6, 10, 22, 42, ...
  pair_vector_iterator_t current_pend = pend.begin() ;
  for ( difference_type pow2 = 2, group_size = 2;
      current_pend + group_size <= pend.end() ;
      pow2 *= 2, group_size = pow2 - group_size) {
    // print pow2, group_size
#if DEBUG
    std::cout << "size(" << size << ") "
      << "pow2(" << pow2 << ") "
      << "group_size(" << group_size << ") "
      << std::endl ;
#endif
    // Binary insert `group_size` elements from pend into chain, reverse order
    pair_vector_iterator_t pe = current_pend + group_size - 1 ;
    while (true) {
      vector_iterator_t chain_end = chain.begin() + (*pe).first ;
      GroupIterator it = (*pe).second ;
#if DEBUG
      std::cout << "size(" << size << ") "
        << "Binary insert "
        << it
        << " until "
        << *std::prev(chain_end)
        << std::endl ;
#endif
      // Find the insertion point by binary search
      typename vector_t::iterator insert_point = std::lower_bound(
          chain.begin(), chain_end, it
          ,GroupIterator::less
          ) ;
      // increment the indices of the elements after the insertion point
      for (pair_vector_iterator_t i = current_pend ; i != pend.end() ; ++i) {
        if ((*i).first >= insert_point - chain.begin()) {
          ++(*i).first ;
        }
      }
      // Insert the element
      chain.insert(insert_point, it) ;
      // If we have inserted all elements, break
      if (pe == current_pend) break ;
      --pe ;
    }
    current_pend += group_size ;
  }
  // If there are pend elements left, insert them into the main chain
  if (current_pend < pend.end()) {
#if DEBUG
    std::cout << "size(" << size << ") "
      << "pend elements left "
      << std::endl ;
#endif
    pair_vector_iterator_t pe = pend.end() ;
    while ( pe != current_pend ) {
      --pe ;
      vector_iterator_t chain_end = chain.begin() + (*pe).first ;
      GroupIterator it = (*pe).second ;
#if DEBUG
      std::cout << "size(" << size << ") "
        << "Binary insert "
        << it
          << " until "
          << *std::prev(chain_end)
        << std::endl ;
#endif
      // Binary search for the insertion point
      typename vector_t::iterator insert_point = std::lower_bound(
          chain.begin(), chain_end, it
          ,GroupIterator::less
          ) ;
      // increment the indices of the elements after the insertion point
      for (pair_vector_iterator_t i = current_pend ; i != pend.end() ; ++i) {
        if ((*i).first >= insert_point - chain.begin()) {
          ++(*i).first ;
        }
      }
      // Insert the element
      chain.insert(insert_point, it) ;
    }
  }
#if DEBUG
  std::cout << "pend: " << std::flush ;
  for (pair_vector_iterator_t pe = pend.begin() ; pe != pend.end() ; ++pe) {
    // pe is an iterator to an iterator of chain
    // *pe is an iterator to an element of chain
    GroupIterator it = (*pe).second ;
    std::cout << " " << it << "(" << (*pe).first << ")";
  }
  std::cout << std::endl ;
#endif
  //////////////////////////////////////////////////////////////////////////
  // Move values back to original container
#if DEBUG
  std::cout
    << "size(" << size << ") "
    << "Move values back to original container" << std::endl ;
#endif
  std::vector<typename GroupIterator::value_type> temp ;
  for (vector_iterator_t chain_it = chain.begin() ; chain_it != chain.end() ; ++chain_it) {
    // insert full elements to temp
    GroupIterator it = *chain_it ;
    temp.insert(temp.end(), it.base(), it.base() + it.size()) ;
  }
#if DEBUG
  std::cout << "temp  : " ;
  print_container(temp) ;
#endif
  // move elements from temp to origin
  std::move(temp.begin(), temp.end(), first.base()) ;
}
#endif
