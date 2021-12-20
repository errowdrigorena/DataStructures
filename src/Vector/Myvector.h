/*
 * Myvector.h
 *
 *  Created on: 9 dic 2021
 *      Author: irodriguezi
 */

#ifndef VECTOR_MYVECTOR_H_
#define VECTOR_MYVECTOR_H_

#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace
{
	constexpr auto from_size_to_capacity = [](std::size_t size)->std::size_t{ return (2*size)+2;};
}

//Notes: This aproach is using 2 aditional memory slots just to acomodate iterators during testing.
template<typename T>
class My_vector {
public:
	struct iterator
	{
	    using iterator_category = std::forward_iterator_tag;
	    using difference_type = std::ptrdiff_t;
	    using value_type = T;
	    using pointer = T*;  // or also value_type*
	    using reference = T&;  // or also value_type&

	    enum class Direction
		{
	    	forward, backward
		};

	private:
	    //Move_behaviour will determine the direction of the ++ operator
	    class Move_behaviour
	    {
	    public:
	    	virtual void operator()(pointer& input) const = 0;
	    	virtual ~Move_behaviour(){};
	    };

	    //Forward_move will determine the FORWARD direction of the ++ operator
	    class Forward_move : public Move_behaviour
	    {
	    public:
	    	void operator()(pointer& input) const override
	    	{
	    		input++;
	    	}
	    	virtual ~Forward_move(){};
	    };

	    //Backward_move will determine the BACKWARD direction of the ++ operator
	    class Backward_move : public Move_behaviour
	    {
	    public:
	    	void operator()(pointer& input) const override
	    	{
	    		input--;
	    	}
	    	virtual ~Backward_move(){};
	    };

	    //change_direction determines the direction the ++ operator of the vector
	    void change_direction (Direction direction)
	    {
	    	if(move_direction_ != nullptr)
	    	{
		    	delete move_direction_;
		    	move_direction_ = nullptr;
	    	}

	    	if (direction == Direction::forward)
	    	{
	    		move_direction_ = new Forward_move();
	    	}
	    	else
	    	{
	    		move_direction_ = new Backward_move();
	    	}
	    };
	public:
	    iterator(pointer ptr, Direction dir = Direction::forward) : ptr_{ptr}, move_direction_{nullptr}
	    {
	    	change_direction(dir);
	    };

	    //it must not delete anything. move_direction_ has 0 size and the iterators will be deleted from My_Vector
	    ~iterator()
	    {
	    	; //do nothing
	    };

	    reference operator*() const { return *ptr_; }
	    pointer operator->() { return ptr_; }

	    // Prefix increment
	    iterator& operator++() { move_direction_->operator ()(ptr_); return *this; }

	    // Postfix increment
	    iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

	    friend bool operator== (const iterator& lhs, const iterator& rhs) { return lhs.ptr_ == rhs.ptr_; };
	    friend bool operator!= (const iterator& lhs, const iterator& rhs) { return lhs.ptr_ != rhs.ptr_; };

	    // shows memory
	    friend std::ostream &operator<<(std::ostream& os, const iterator& it)
	    {
	    	os <<  it.ptr_;
	    	return os;
	    }
	private:
	    pointer ptr_;
	    Move_behaviour* move_direction_;
	};

  My_vector(std::initializer_list<T> i_list) : size_{i_list.size() }, capacity_{from_size_to_capacity(size_)}, values_{new T[capacity_]{} }
  {
	std::copy(i_list.begin(), i_list.end(), values_+1); //the first position is leaved empty in order to enable automatic_tests
  }
  explicit My_vector(std::size_t size) : size_{size}, capacity_{from_size_to_capacity(size_) }, values_{new T[capacity_]{} } {}
  My_vector() : size_{0 }, capacity_{25}, values_{new T[capacity_]{} } {}

  My_vector(const My_vector& copyable) : size_{copyable.size_ }, capacity_{copyable.capacity_}, values_{new T[capacity_]{} }
  {
	values_ = 0;
	std::copy(copyable.begin(), copyable.end(), values_+1); //the first position is leaved empty in order to enable automatic_tests
  }

  My_vector operator= (const My_vector& input)
  {
	  size_ = input.size_;
	  capacity_ = input.capacity_;
	  delete[] values_;
	  values_ = new T[capacity_];
	  std::copy(input.begin(), input.end(), values_);
  }

  ~My_vector()
  {
	  delete[] values_;
  }

  //shows size and useful content of My_vector
  friend std::ostream &operator<<(std::ostream& os, const My_vector& vector)
  {
	os << "size = " << vector.size_;
	os << std::endl << "content = ";
	std::copy(vector.values_+1, vector.values_ + vector.size_+1, std::ostream_iterator<T>(os, " "));
	return os << std::endl;
  }

  iterator begin() const
  {
	  iterator output{values_+1};
	  return output;
  }

  iterator end() const
  {
	  iterator output{values_ + size_+1};
	  return output;
  }

  iterator rbegin() const
  {
	  iterator output{values_ + size_, iterator::Direction::backward};
	  return output;
  }

  iterator rend() const
  {
	  iterator output{values_, iterator::Direction::backward};
	  return output;
  }

  //size returns the amount of useful elements in My_vector
  std::size_t size(){return size_; }

  //operator[] providen random access
  T& operator[](std::size_t index)
  {
      if (index >= size_) {
    	  //throw exception
    	  throw std::invalid_argument("Array index out of bounds");
      }
      return values_[index+1];
  }

  //returns the first useful value
  T front()
  {
	  return values_[1];
  }

  //returns the last useful value
  T back()
  {
	  return values_[size_];
  }
  //push_back inserts
  void push_back(T input)
  {
	  check_increase();
	  values_[size_+1] = input;
	  size_++;
  }

  //empty returns true if there is not useful information and false in any other case
  bool empty()
  {
	  return size_ == 0;
  }

private:
  	//check_increase ensures the dinamicity of the vector
  	void check_increase()
  	{
  		if( ( size_+2 ) > capacity_)
  		{
  			capacity_ *= 2;
  			T* n_values{new T[capacity_]{} };
  			std::swap(values_, n_values);
  			delete[] values_;
  			values_ = n_values;
  		}
  	}

	std::size_t size_;
	std::size_t capacity_;
	T* values_;
};

#endif /* VECTOR_MYVECTOR_H_ */
