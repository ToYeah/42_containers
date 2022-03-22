#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <iterator>
#include <memory>

#include "Random_access_iterator.hpp"
#include "Reverse_iterator.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef const typename allocator_type::pointer const_pointer;
  typedef ft::ra_iterator<value_type> iterator;
  typedef ft::ra_iterator<const value_type> const_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;

 protected:
  pointer first_;
  pointer last_;
  pointer end_of_storage_;
  size_type size_;
  allocator_type allocater_;

 public:
  vector()
      : first_(NULL),
        last_(NULL),
        end_of_storage_(NULL),
        size_(0),
        allocater_(allocator_type()){};

  explicit vector(const Allocator& alloc)
      : first_(NULL),
        last_(NULL),
        end_of_storage_(NULL),
        size_(0),
        allocater_(alloc){};

  explicit vector(size_type count, const T& value = T(),
                  const Allocator& alloc = Allocator())
      : first_(NULL),
        last_(NULL),
        end_of_storage_(NULL),
        size_(0),
        allocater_(alloc) {
    construct_storage(count, value);
  };

  template <class InputIt>
  vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      : first_(NULL),
        last_(NULL),
        end_of_storage_(NULL),
        size_(0),
        allocater_(alloc) {
    construct_storage(std::distance(first, last));
    iterator dest_it = begin();
    for (InputIt src_it = first; src_it != last;) {
      dest_it++ = src_it++;
    }
  };

  vector(const vector& other){};  // TODO

  iterator begin() { return iterator(first_); }
  const_iterator begin() const { return const_iterator(first_); }

  iterator end() { return iterator(last_); }
  const_iterator end() const { return const_iterator(last_); }

  reverse_iterator rbegin() { return reverse_iterator(end()); };
  const_reverse_iterator rbegin() const { return reverse_iterator(end()); };

  reverse_iterator rend() { return reverse_iterator(begin()); };
  const_reverse_iterator rend() const { return reverse_iterator(begin()); };

 private:
  void construct_storage(size_type size, const T& value = T()) {
    pointer tmp = allocater_.allocate(size);
    first_ = new (tmp) T(value);
    last_ = first_;
    size_ = size;
    end_of_storage_ = first_ + size;
  }
};
}  // namespace ft

#endif /* ********************************************************** VECTOR_H \
        */