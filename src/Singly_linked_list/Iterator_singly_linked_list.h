/*
 * Iterator_singly_linked_list.h
 *
 *  Created on: Jan 10, 2022
 *      Author: iban
 */

#ifndef SINGLY_LINKED_LIST_ITERATOR_SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_ITERATOR_SINGLY_LINKED_LIST_H_

#include <iterator>
#include <Singly_linked_list/Node_singly_linked_list.h>

template<typename T>
class Iterator_singly_linked_list : public std::iterator<std::forward_iterator_tag, Node_singly_linked_list<T>>
{
  using Node = Node_singly_linked_list<T>;
  using iterator = Iterator_singly_linked_list;
public:
  using pointer = typename std::iterator<std::forward_iterator_tag, Node>::pointer;
  using reference = T&;

  Iterator_singly_linked_list(pointer ptr) : ptr_{ptr }{}
  ~Iterator_singly_linked_list(){ ; /*do nothing*/}

 reference operator*() const { return ptr_->value_; }
 pointer operator->() { return ptr_; }
  // Prefix increment
 iterator& operator++() { ptr_ = ptr_->next_; return *this; }

 // Postfix increment
 iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

 friend bool operator== (const iterator& lhs, const iterator& rhs) { return lhs.ptr_ == rhs.ptr_; }
 friend bool operator!= (const iterator& lhs, const iterator& rhs) { return lhs.ptr_ != rhs.ptr_; }

 // shows memory
 friend std::ostream &operator<<(std::ostream& os, const iterator& it) { os <<  it.ptr_; return os; }
private:
  pointer ptr_;
};



#endif /* SINGLY_LINKED_LIST_ITERATOR_SINGLY_LINKED_LIST_H_ */
