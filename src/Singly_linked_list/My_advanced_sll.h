/*
 * My_advanced_sll.h
 *
 *  Created on: Jan 12, 2022
 *      Author: iban
 */

#ifndef SINGLY_LINKED_LIST_MY_ADVANCED_SLL_H_
#define SINGLY_LINKED_LIST_MY_ADVANCED_SLL_H_
#include <Singly_linked_list/My_Singly_linked_list.h>

//the purpose of this class is to support sorting
template<typename T>
class My_advanced_sll : public My_Singly_linked_list<T>
{
  using Node = Node_singly_linked_list<T>;
  using iterator = Iterator_singly_linked_list<T>;
public:
  My_advanced_sll() : My_advanced_sll::My_Singly_linked_list{} {};
  My_advanced_sll(std::initializer_list<T> i_list) : My_advanced_sll::My_Singly_linked_list{i_list} {};
  My_advanced_sll(const My_advanced_sll& copiable) : My_advanced_sll::My_Singly_linked_list{copiable} {};
  My_advanced_sll( const My_advanced_sll&& input ) = delete;
  virtual ~My_advanced_sll(){};
  My_advanced_sll operator= (const My_advanced_sll& assignable);

  T& operator[] (std::size_t index){ return this->at(index); }; //tricky

  iterator get_min(); //returns an iterator to the first minimum value
  iterator get_max(); //returns an iterator to the first maximum value

  void sort_by_value(std::function<bool(T,T)> comparer = std::less<T>()); //it will only change the value of the node
  void sort_by_node(std::function<bool(T,T)> comparer = std::less<T>()); //the nodes will be rearranged

  iterator find_prev(){return this->find_previous(this->header_); };
private:
  iterator get_min_or_max_it(std::function<bool(T,T)> comparer);
  Node* get_min_or_max_node(std::function<bool(T,T)> comparer);

  void bubble_sort_core(Node *input, std::function<bool(T,T)> comparer);
};

template<typename T>
  My_advanced_sll<T> My_advanced_sll<T>::operator =(const My_advanced_sll& assignable)
  {
    return My_advanced_sll::My_Singly_linked_list.operator =(assignable);
  }

template<typename T>
  typename My_advanced_sll<T>::iterator My_advanced_sll<T>::get_min()
  {
    return get_min_or_max_it(std::greater<T>());
  }

template<typename T>
  typename My_advanced_sll<T>::iterator My_advanced_sll<T>::get_max()
  {
    return get_min_or_max_it(std::less<T>());
  }

template<typename T>
  typename My_advanced_sll<T>::iterator My_advanced_sll<T>::get_min_or_max_it(std::function<bool(T,T)> comparer)
  {
    iterator compared_iterator{get_min_or_max_node(comparer) };
    return compared_iterator;
  }

template<typename T>
  typename My_advanced_sll<T>::Node* My_advanced_sll<T>::get_min_or_max_node(std::function<bool(T,T)> comparer)
  {
    Node* evaluated = this->header_;
    auto evaluation_getter = [&](Node *input)
	{
	  if( comparer(evaluated->value_, input->value_ ) )
	    {
	      evaluated = input;
	    }
	};
    this->operate_list (this->size()-1, evaluation_getter);

    return evaluated;
  }

template<typename T>
  void My_advanced_sll<T>::sort_by_value(std::function<bool(T,T)> comparer)
  {
    if(this->size_ < 2)
      {
	return;
      }

    auto evaluation = [&](Node* input)
	{
	  auto moving_node = input->next_;
	  while ( moving_node != nullptr )
	    {
	      if( comparer(moving_node->value_, input->value_) )
		{
		  auto aux_value = input->value_;
		  input->value_= moving_node->value_;
		  moving_node->value_ = aux_value;
		}
	      moving_node = moving_node->next_;
	    }
	};

    this->operate_list (this->size_-1, evaluation);
  }

template<typename T>
  void My_advanced_sll<T>::bubble_sort_core(Node* input, std::function<bool(T,T)> comparer)
  {
    auto moving_node = input->next_;
    auto actual_node = input;

    while ( moving_node != nullptr )
      {
	if( comparer(moving_node->value_, actual_node->value_) )
	  {
	    auto prev_moving = this->find_previous(moving_node);
	    auto prev_actual = this->find_previous(actual_node);

	    auto aux_actual_next = actual_node->next_;
	    actual_node->next_ = moving_node->next_;

	    if( this->tail_ == moving_node )
	      {
		this->tail_ = actual_node;
	      }

	    if( aux_actual_next != moving_node )
	      {
		    moving_node->next_ = aux_actual_next;
		    prev_moving->next_ = actual_node;
	      }
	    else
	      {
		    moving_node->next_ = actual_node;
	      }

	    if(this->header_ == actual_node)
	      {
		this->header_ = moving_node;
	      }
	    else
	      {
		prev_actual->next_ = moving_node;
	      }

	    actual_node = moving_node;
	    //std::cout << "In buble core" << std::endl;
	    //std::cout << *this << std::endl;
	  }
	moving_node = moving_node->next_;
      }
  }

template<typename T>
  void My_advanced_sll<T>::sort_by_node(std::function<bool(T,T)> comparer)
  {
    if(this->size_ < 2)
      {
	return;
      }

    auto actual_node = this->header_;
    std::size_t hop_number{0 };
    while( actual_node->next_ != nullptr && hop_number < (this->size_-1) )
      {
	bubble_sort_core(actual_node, comparer);
	hop_number++;
	actual_node = this->hoper(hop_number);
	//std::cout << *this << std::endl;
      }
  }
#endif /* SINGLY_LINKED_LIST_MY_ADVANCED_SLL_H_ */
