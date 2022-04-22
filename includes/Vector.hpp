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
    first_ = allocate(count);
    last_ = first_ + count;
    end_of_storage_ = first_ + count;
    for (iterator it = begin(); it != end(); it++) {
      construct(&(*it), value);
    }
  };

  template <class InputIt>
  vector(InputIt first,
         typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
         const Allocator& alloc = Allocator())
      : first_(NULL), last_(NULL), end_of_storage_(NULL), allocater_(alloc) {
    construct_storage(std::distance(first, last));
  };  // TODO

  vector(const vector& other) { *this = other; };

  ~vector() {
    clear();
    deallocate();
  }

  vector& operator=(const vector& other) {
    if (this != &other) {
      construct_storage(other.capacity());
      std::copy(other.begin(), other.end(), this->begin());
      last_ = first_ + other.size();
      end_of_storage_ = first_ + other.capacity();
    }
    return *this;
  }

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

  iterator erase(iterator position) {
    difference_type distance = std::distance(begin(), position);
    std::copy(position + 1, end(), position);
    last_ -= 1;
    destroy(last_);
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

 private:
  void construct_storage(size_type size, const T& value = T()) {
    first_ = allocater_.allocate(size);
    std::uninitialized_fill_n(first_, size, value);
    last_ = first_ + size;
    end_of_storage_ = first_ + size;
  }

  void destroy_elem(pointer target) { allocater_.destroy(target); };

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
};
}  // namespace ft

#endif /* ********************************************************** VECTOR_H \
        */