#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>

#include "Enable_if.hpp"
#include "Random_access_iterator.hpp"
#include "Reverse_iterator.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::pointer const_pointer;
  typedef ft::ra_iterator<pointer> iterator;
  typedef ft::ra_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

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
    resize(count, value);
  };

  template <class InputIt>
  vector(InputIt first,
         typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
         const Allocator& alloc = Allocator())
      : first_(NULL), last_(NULL), end_of_storage_(NULL), allocater_(alloc) {
    insert(begin(), first, last);
  };

  vector(const vector& other) { *this = other; };

  ~vector() {
    clear();
    deallocate();
  }

  vector& operator=(const vector& other) {
    if (this != &other) {
      assign(other.begin(), other.end());
    }
    return *this;
  }

  // Iterators-------------------------------------------

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

  // Capacity-------------------------------------------

  size_type size() const { return std::distance(begin(), end()); }

  size_type max_size() const {
    return std::min<size_type>(std::numeric_limits<difference_type>::max(),
                               allocater_.max_size());
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n < size()) {
      erase(begin() + n, end());
    } else if (n > size()) {
      insert(end(), n - size(), val);
    }
  };

  size_type capacity() const {
    return std::distance(begin(), iterator(end_of_storage_));
  };

  bool empty() const { return size() == 0; };

  void reserve(size_type n) {
    if (capacity() >= n) return;

    iterator old_begin = begin();
    iterator old_end = end();
    reverse_iterator old_rbegin = rbegin();
    reverse_iterator old_rend = rend();
    pointer old_first = first_;
    size_type old_cap = capacity();
    size_type old_size = size();

    first_ = allocate(n);
    last_ = first_ + old_size;
    end_of_storage_ = first_ + n;

    for (size_t i = 0; (old_begin + i) != old_end; i++) {
      construct(first_ + i, *(old_begin + i));
    }

    for (reverse_iterator rit = old_rbegin; rit != old_rend; rit++) {
      destroy(&(*rit));
    }
    allocater_.deallocate(old_first, old_cap);
  }

  // Element access-------------------------------------

  reference operator[](size_type pos) { return first_[pos]; }

  const_reference operator[](size_type pos) const { return first_[pos]; }

  reference at(size_type pos) {
    if (!(pos < size())) {
      throw std::out_of_range("");
    }
    return first_[pos];
  }

  const_reference at(size_type pos) const {
    if (!(pos < size())) {
      throw std::out_of_range("");
    }
    return first_[pos];
  }

  reference front() { return *begin(); }

  const_reference front() const { return *begin(); }

  reference back() {
    iterator tmp = end();
    --tmp;
    return *tmp;
  }

  const_reference back() const {
    const_iterator tmp = end();
    --tmp;
    return *tmp;
  }

  // Modifiers------------------------------------------

  void assign(size_type count, const T& value) {
    size_type old_size = size();

    reserve(calc_new_cap(count));
    last_ = first_;
    for (size_type i = 0; i < count; i++, last_++) {
      construct(first_ + i, value);
    }

    if (old_size > count) {
      destroy_until(rbegin() + old_size - count);
    }
  }

  template <class InputIt>
  void assign(
      InputIt first,
      typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
    size_type old_size = size();
    size_type distance = std::distance(first, last);

    reserve(calc_new_cap(distance));
    last_ = first_;
    for (size_type i = 0; i < distance; i++, last_++) {
      construct(first_ + i, *(first + i));
    }

    if (old_size > distance) {
      destroy_until(rbegin() + old_size - distance);
    }
  }

  iterator insert(iterator pos, const T& value) {
    reserve(calc_new_cap(size() + 1));
    insert(pos, 1, value);
    return pos;
  }

  void insert(iterator pos, size_type count, const T& value) {
    pos = insert_helper(pos, count);
    std::fill_n(pos, count, value);
  }

  template <class InputIt>
  void insert(
      iterator pos,
      typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
      InputIt last) {
    pos = insert_helper(pos, std::distance(first, last));
    std::copy(first, last, pos);
  }

  iterator erase(iterator position) {
    std::copy(position + 1, end(), position);
    destroy_until(rbegin() + 1);
    return position;
  };

  iterator erase(iterator first, iterator last) {
    difference_type len = std::distance(first, last);
    std::copy(last, end(), first);
    destroy_until(rbegin() + len);
    return first;
  };

 private:
  pointer allocate(size_type n) { return allocater_.allocate(n); }

  void deallocate() { return allocater_.deallocate(first_, capacity()); }

  void construct(pointer ptr) { allocater_.construct(ptr); }

  void construct(pointer ptr, const_reference value) {
    allocater_.construct(ptr, value);
  }

  void destroy(pointer ptr) { allocater_.destroy(ptr); }

  void destroy_until(reverse_iterator rend) {
    for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_) {
      destroy(&(*riter));
    }
  }

  void clear() { destroy_until(rend()); }

  size_type calc_new_cap(size_type new_cap) {
    size_type current_cap = capacity();
    if (current_cap >= new_cap) return current_cap;
    return std::max(current_cap * 2, new_cap);
  }

  iterator insert_helper(iterator pos, size_type count) {
    if (capacity() < size() + count) {
      difference_type offset_size = std::distance(begin(), pos);
      reserve(calc_new_cap(size() + 1));
      pos = begin() + offset_size;
    }

    std::uninitialized_fill_n(end(), count, T());
    std::copy_backward(pos, end(), iterator(last_ + count));
    last_ += count;
    return pos;
  }
};
}  // namespace ft

#endif /* ********************************************************** VECTOR_H \
        */