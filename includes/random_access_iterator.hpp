#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include "Iterator.hpp"
#include "Iterator_traits.hpp"

namespace ft {
template <typename Iterator>
class ra_iterator {  // public iterator
 protected:
  Iterator current_;
  typedef iterator_traits<Iterator> traits_type_;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type_::iterator_category iterator_category;
  typedef typename traits_type_::value_type value_type;
  typedef typename traits_type_::difference_type difference_type;
  typedef typename traits_type_::reference reference;
  typedef typename traits_type_::pointer pointer;

  ra_iterator() : current_(NULL){};
  explicit ra_iterator(iterator_type x) : current_(x){};
  template <class Iter>
  ra_iterator(const ra_iterator<Iter>& it) : current_(it.base()){};
  ~ra_iterator(){};

  ra_iterator& operator=(const ra_iterator& rhs) {
    if (this != &rhs) {
      current_ = rhs.current_;
    }
    return *this;
  };

  reference operator*() const { return *current_; };

  pointer operator->() const { return &(operator*()); };

  ra_iterator operator+(difference_type n) const {
    return ra_iterator(current_ + n);
  };

  ra_iterator operator-(difference_type n) const {
    return ra_iterator(current_ - n);
  };

  ra_iterator& operator+=(difference_type n) {
    current_ += n;
    return *this;
  };

  ra_iterator& operator-=(difference_type n) {
    current_ -= n;
    return *this;
  };

  ra_iterator& operator++() {
    ++current_;
    return *this;
  };

  ra_iterator operator++(int) {
    ra_iterator tmp = *this;
    ++current_;
    return tmp;
  }

  ra_iterator& operator--() {
    --current_;
    return *this;
  };

  ra_iterator operator--(int) {
    ra_iterator tmp = *this;
    --current_;
    return tmp;
  }
  reference operator[](difference_type n) const { return current_[n]; };

  iterator_type base() const { return current_; }
};

template <class Iterator1, class Iterator2>
bool operator==(const ra_iterator<Iterator1>& lhs,
                const ra_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator!=(const ra_iterator<Iterator1>& lhs,
                const ra_iterator<Iterator2>& rhs) {
  return lhs.base() != rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator>(const ra_iterator<Iterator1>& lhs,
               const ra_iterator<Iterator2>& rhs) {
  return lhs.base() > rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator<(const ra_iterator<Iterator1>& lhs,
               const ra_iterator<Iterator2>& rhs) {
  return lhs.base() < rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator>=(const ra_iterator<Iterator1>& lhs,
                const ra_iterator<Iterator2>& rhs) {
  return lhs.base() >= rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator<=(const ra_iterator<Iterator1>& lhs,
                const ra_iterator<Iterator2>& rhs) {
  return lhs.base() <= rhs.base();
};

template <class Iterator>
ra_iterator<Iterator> operator+(
    typename ra_iterator<Iterator>::difference_type n,
    const ra_iterator<Iterator>& it) {
  return ra_iterator<Iterator>(it.base() + n);
};

template <class Iterator1, class Iterator2>
typename ra_iterator<Iterator1>::difference_type operator-(
    const ra_iterator<Iterator1>& lhs, const ra_iterator<Iterator2>& rhs) {
  return lhs.base() - rhs.base();
};
}  // namespace ft

#endif /* ****************************************** RANDOM_ACCESS_ITERATOR_H \
        */