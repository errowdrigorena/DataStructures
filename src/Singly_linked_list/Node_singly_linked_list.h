/*
 * Node_singly_linked_list.h
 *
 *  Created on: Jan 10, 2022
 *      Author: iban
 */

#ifndef SINGLY_LINKED_LIST_NODE_SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_NODE_SINGLY_LINKED_LIST_H_

template<typename T>
class Node_singly_linked_list
{
public:
  Node_singly_linked_list(T value, Node_singly_linked_list *next = nullptr) : value_{value }, next_{next }{};
  ~Node_singly_linked_list(){};
  T value_;
  Node_singly_linked_list *next_;
};



#endif /* SINGLY_LINKED_LIST_NODE_SINGLY_LINKED_LIST_H_ */
