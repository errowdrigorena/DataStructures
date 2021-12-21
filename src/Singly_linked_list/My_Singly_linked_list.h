/*
 * My_Singly_linked_list.cc
 *
 *  Created on: Dec 21, 2021
 *      Author: iban
 */

#ifndef SINGLY_LINKED_LIST_MY_SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_MY_SINGLY_LINKED_LIST_H_
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <functional>

template<typename T> class My_Singly_linked_list;
template<typename T> std::ostream & operator<<(std::ostream& os, const My_Singly_linked_list<T>& sll);
//note: the previous declarations are needed in order to put operator<< outside the class{}

template<typename T>
  class My_Singly_linked_list
  {
    class Node
    {
    public:
      Node(T value, Node *next = nullptr) : value_{value }, next_{next }{};
      ~Node(){};
      T value_;
      Node *next_;
    };

  public:
    My_Singly_linked_list (std::initializer_list<T> i_list);
    ~My_Singly_linked_list();
    //size returns the amount of useful elements in My_Singly_linked_list
    std::size_t size() const {return size_; }

    //operator[] provides random access
    T& operator[] (std::size_t index);

    //shows size and useful content of My_Singly_linked_list
    friend std::ostream &operator<< <T>(std::ostream& os, const My_Singly_linked_list& sll);

    //inserts a value after the actual tail_ (last value)
    void push_back(T value);
    //inserts a value before the actual header (first value)
    void push_front(T value);

    //gets header_ value (first value)
    T front() const {header_->value_; }
    //gets tail_ value (last value)
    T back() const {tail_->value_; }

    //empty returns true if there is not useful information and false in any other case
    bool empty() const { return size_ == 0;}
  private:
    Node* operate_list(std::size_t index, std::function<void (Node*)> callback = [](Node*){; /*Do nothing*/}) const;
    std::size_t size_;
    Node *header_;
    Node *tail_;
  };

template<typename T>
  T& My_Singly_linked_list<T>::operator[] (std::size_t index)
  {
    Node *aux_node = operate_list (--index);

    return aux_node->value_;
  }

template<typename T>
  void My_Singly_linked_list<T>::push_back(T value)
  {
    Node *last = new Node{value };
    tail_->next_ = last;
    tail_ = last;
    size_++;
  }

template<typename T>
  void My_Singly_linked_list<T>::push_front (T value)
  {
    Node *first = new Node{value, header_ };
    header_ = first;
    size_++;
  }

template<typename T>
  typename My_Singly_linked_list<T>::Node*
  My_Singly_linked_list<T>::operate_list(std::size_t index, std::function
					 <void(typename My_Singly_linked_list<T>::Node*)> callback) const
  {
    if (index >= size_)
      {
	//throw exception
	throw std::invalid_argument ("Array index out of bounds");
      }

    auto aux_node = header_;

    for (std::size_t i = 0; i <= index; i++)
      {
	callback (aux_node);
	aux_node = aux_node->next_;
      }

    return aux_node;
  }

template<typename T>
  My_Singly_linked_list<T>::~My_Singly_linked_list ()
  {
    for (std::size_t i = 2; i <= size_; i++)
      {
	auto deleteable = operate_list(size_ - i);
	std::cout << "Add: " << deleteable << " will be deleted" << std::endl;
	delete deleteable;
      }
    if(header_)
      {
	std::cout << "Add: " << header_ << " will be deleted" << std::endl;
	delete header_;
      }
  }

template<typename T>
  My_Singly_linked_list<T>::My_Singly_linked_list (std::initializer_list<T> i_list) : size_{i_list.size() }, header_{nullptr }, tail_{nullptr }
  {
    if (size_ > 0)
      {
	Node *aux_prev{nullptr };
	for (auto it = i_list.begin (); it != i_list.end (); it++)
	  {
	    Node *insertable_node = new Node{*it };

	    if (it == i_list.begin ())
	      {
		header_ = insertable_node;
	      }
	    else
	      {
		aux_prev->next_ = insertable_node;
	      }

	    aux_prev = insertable_node;
	  }

	tail_ = aux_prev;

	if (size_ == 1)
	  {
	    tail_ = header_;
	  }
      }
  }

template<typename T>
  std::ostream & operator<<(std::ostream& os, const My_Singly_linked_list<T>& sll)
  {
    os << "size = " << sll.size_ << std::endl;
    os << "header ADD = " << sll.header_ << std::endl;
    os << "tail ADD = " << sll.tail_ << std::endl;

    os << std::endl << "content = ";

    auto print = [&](typename My_Singly_linked_list<T>::Node *input){ os << input->value_ << " ";};
    std::size_t aux_size = sll.size_ - 1;
    sll.operate_list (aux_size, print);

    return os << std::endl;
  }
#endif /* SINGLY_LINKED_LIST_MY_SINGLY_LINKED_LIST_CC_ */
