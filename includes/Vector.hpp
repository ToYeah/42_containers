#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
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
  allocator_type allocater_;

 public:
  vector()
      : first_(NULL),
        last_(NULL),
        end_of_storage_(NULL),
        allocater_(allocator_type()){};

  explicit vector(const Allocator& alloc)
      : first_(NULL), last_(NULL), end_of_storage_(NULL), allocater_(alloc){};

  explicit vector(size_type count, const T& value = T(),
                  const Allocator& alloc = Allocator())
      : first_(NULL), last_(NULL), end_of_storage_(NULL), allocater_(alloc) {
    construct_storage(count, value);
  };

  template <class InputIt>
  vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      : first_(NULL), last_(NULL), end_of_storage_(NULL), allocater_(alloc) {
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
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  };

  reverse_iterator rend() { return reverse_iterator(begin()); };
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  };

  size_type size() const { return std::distance(begin(), end()); }

  size_type max_size() const {
    return std::distance(begin(), iterator(end_of_storage_));
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n < size()) {
      erase(begin() + n, end());
    } else if (n > size()) {
      insert(end(), n - size(), val);
    }
  };

  size_type capacity() const {
    return std::distance(end(), iterator(end_of_storage_));
  };

  bool empty() const { return size() == 0; };

  void reserve(size_type n) {}

  iterator erase(iterator position) {
    difference_type distance = std::distance(begin(), position);
    if (position + 1 != end()) {
      std::copy(position + 1, end(), position);
    }
    last_ -= 1;
    destroy_elem(last_);
    return begin() + distance;
  };

  iterator erase(iterator first, iterator last) {
    difference_type len = std::distance(first, last);

    std::copy(last, end(), first);
    for (iterator it = first + std::distance(last, end()); it != end(); it++) {
      destroy_elem(it);
    }
    last_ -= len;
    return first;
  };

 private:
  void construct_storage(size_type size, const T& value = T()) {
    pointer tmp = allocater_.allocate(size);
    first_ = new (tmp) T(value);
    last_ = first_;
    end_of_storage_ = first_ + size;
  }

  void destroy_elem(pointer target) { allocater_.destroy(target); };
};
}  // namespace ft

#endif /* ********************************************************** VECTOR_H \
        */