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
#include <algorithm>
#include <Singly_linked_list/Node_singly_linked_list.h>
#include <Singly_linked_list/Iterator_singly_linked_list.h>
#include <vector>

template<typename T> class My_Singly_linked_list;
template<typename T> std::ostream & operator<<(std::ostream& os, const My_Singly_linked_list<T>& sll);
//note: the previous declarations are needed in order to put operator<< outside the class{}

template<typename T>
  class My_Singly_linked_list
  {
    using Node = Node_singly_linked_list<T>;
    using iterator = Iterator_singly_linked_list<T>;
  public:
    My_Singly_linked_list (std::initializer_list<T> i_list);
    My_Singly_linked_list () : size_{0 }, header_{nullptr }, tail_{nullptr }{};
    My_Singly_linked_list( const My_Singly_linked_list& input );

    ~My_Singly_linked_list();
    //size returns the amount of useful elements in My_Singly_linked_list
    std::size_t size() const {return size_; }

    //operator[] provides random access
    T& operator[] (std::size_t index);

    //assignment operator
    My_Singly_linked_list operator= (const My_Singly_linked_list& input);

    //shows size and useful content of My_Singly_linked_list
    friend std::ostream &operator<< <T>(std::ostream& os, const My_Singly_linked_list& sll);

    //inserts a value after the actual tail_ (last value)
    void push_back(T value);
    //inserts a value before the actual header (first value)
    void push_front(T value);

    //gets header_ value (first value)
    T front() const {return header_->value_; }
    //gets tail_ value (last value)
    T back() const {return tail_->value_; }

    //gets an iterator to the Node which contains the first match the search value
    iterator find_first(T searchable) const;
    //gets the number of times a value is contained
    std::size_t find_ocurrences (T searchable) const;

    //erase first node with a given value if any
    void erase_first_ocurrence(T eraseable);
    //erase every node with a given value if any
    void erase_every_ocurrence(T eraseable);
    //erase every repeated value
    void erase_reps();

    iterator begin() const;
    iterator end() const;

    //empty returns true if there is not useful information and false in any other case
    bool empty() const { return size_ == 0;}
  private:
    //this function is used to move. Index represents the last index that will ackire ->next.
    //that is why maximum index is size_ - 1, which represents last node index.
    Node* operate_list(std::size_t index, std::function<void (Node*)> callback = [](Node*){; /*Do nothing*/}) const;
    //gets an iterator to the Node which contains the node before the selected node, if exist and end() if it doesn't
    iterator find_previous(Node* searchable) const;
    void erase_node(Node* eraseable);
    void erase_nodes();

    std::size_t size_;
    Node *header_;
    Node *tail_;
  };

template<typename T>
My_Singly_linked_list<T>::My_Singly_linked_list( const My_Singly_linked_list& input )
  : size_{0 }, header_{nullptr }, tail_{nullptr }
  {
    for(auto& it : input)
	  {
	    push_back(it.value_);
	  }
  }

template<typename T>
  My_Singly_linked_list<T> My_Singly_linked_list<T>::operator= (const My_Singly_linked_list& input)
  {
    erase_nodes();

    My_Singly_linked_list a_copy{input };
    std::swap(this->header_, a_copy.header_);
    std::swap(this->tail_, a_copy.tail_);
    std::swap(this->size_, a_copy.size_);

    return *this;
  }

template<typename T>
  T& My_Singly_linked_list<T>::operator[] (std::size_t index)
  {
    if(index == 0)
      {
	return header_->value_;
      }

    Node *aux_node = operate_list (--index);

    return aux_node->value_;
  }

template<typename T>
  void My_Singly_linked_list<T>::push_back(T value)
  {
    Node *last = new Node{value };
    if(header_ != nullptr)
      {
	tail_->next_ = last;
      }
    else
      {
	header_ = last;
      }
    tail_ = last;
    size_++;
  }

template<typename T>
  void My_Singly_linked_list<T>::push_front (T value)
  {
    Node *first = new Node{value, header_ };
    header_ = first;
    if(tail_ == nullptr)
      {
	tail_ = header_;
      }
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
	throw std::invalid_argument ("Index out of bounds");
      }

    auto aux_node = header_;

    for (std::size_t i = 0; i <= index && aux_node != nullptr; i++)
      {
	auto next_node = aux_node->next_;
	callback (aux_node);
	aux_node = next_node;
      }

    return aux_node;
  }

template<typename T>
  void My_Singly_linked_list<T>::erase_nodes ()
  {
    for (std::size_t i = 2; i <= size_; i++)
      {
	  auto deleteable = operate_list(size_ - i);
	  //std::cout << "Add: " << deleteable << " will be deleted" << std::endl;
	  delete deleteable;
      }
    if(header_)
      {
	  //std::cout << "Add: " << header_ << " will be deleted" << std::endl;
	  delete header_;
      }
  }

template<typename T>
void My_Singly_linked_list<T>::erase_node(Node* eraseable)
{
  if(eraseable == nullptr)
    {
      throw std::invalid_argument ("nullptr cannot be deleted");
    }

  if(eraseable == header_)
    {
      if(size_ == 1)
	{
	  header_ = tail_ = nullptr;
	}
      else
	{
	  header_ = header_->next_;
	}
    }
  else
    {
      auto previous = find_previous(eraseable);
      previous->next_ = eraseable->next_;
    }

  size_--;
  //std::cout << "Add: " << eraseable << " will be deleted" << std::endl;
  delete eraseable;
}

template<typename T>
  My_Singly_linked_list<T>::~My_Singly_linked_list ()
  {
    erase_nodes();
  }

template<typename T>
  void My_Singly_linked_list<T>::erase_first_ocurrence(T eraseable)
{
  auto actual_node = header_;
  while( actual_node != end() )
    {
      if (actual_node->value_ == eraseable)
	{
	  erase_node(actual_node);
	  break;
	}
      actual_node = actual_node->next_;
    }
}

template<typename T>
  void My_Singly_linked_list<T>::erase_every_ocurrence(T eraseable)
{
  auto erase_node_by_value = [&](typename My_Singly_linked_list<T>::Node *input){
    if(input->value_ == eraseable)
      {
	erase_node(input);
      }
  };

  operate_list (size_-1, erase_node_by_value);
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
typename My_Singly_linked_list<T>::iterator My_Singly_linked_list<T>::begin() const
    {
      typename My_Singly_linked_list<T>::iterator first{header_ };
      return first;
    }

template<typename T>
typename My_Singly_linked_list<T>::iterator My_Singly_linked_list<T>::end() const
    {
      if(tail_ == nullptr)
	{
	  return tail_;
	}
      typename My_Singly_linked_list<T>::iterator last{tail_->next_ }; //by definition should be nullptr
      return last;
    }

template<typename T>
typename My_Singly_linked_list<T>::iterator My_Singly_linked_list<T>::find_first(T searchable) const
  {
    auto output = begin();
    while( output->value_ != searchable && output != end() )
      {
	output++;
      }
    return output;
  }

template<typename T>
typename My_Singly_linked_list<T>::iterator My_Singly_linked_list<T>::find_previous(Node* searchable) const
  {
    auto output = begin();
    while( output->next_ != searchable && output != end() )
      {
	output++;
      }
    return output;
  }

template<typename T>
std::size_t My_Singly_linked_list<T>::find_ocurrences(T searchable) const
  {
    std::size_t ocurrences{0 };
    std::for_each(begin(), end(), [&](T value){
      if(value == searchable)
	{
	  ocurrences++;
	}
    });
    return ocurrences;
  }

template<typename T>
void My_Singly_linked_list<T>::erase_reps()
  {
    //if we would know that the set is an array based tree, set might be a better choice
    //as we don't, it sounds absurd to implement a data structure which may be based on
    //the type we are implementing
    std::vector<T> ocurred;
    ////////////////////////////////////////////////////////////////////////////////////

    std::vector<Node*> eraseable_nodes;
    ocurred.reserve(size_);
    eraseable_nodes.reserve(size_);

    auto identify_repeated_node = [&](typename My_Singly_linked_list<T>::Node *input){
      auto it = std::find(ocurred.begin(), ocurred.end(), input->value_);

      if( it != ocurred.end() )
        {
	  eraseable_nodes.push_back(input);
        }
      else
	{
	  ocurred.push_back(input->value_);
	}
    };

    operate_list (size_-1, identify_repeated_node);

    std::for_each(eraseable_nodes.begin(), eraseable_nodes.end(), [&](Node* node)
		  { erase_node(node); });
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
