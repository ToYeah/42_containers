#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "Iterator.hpp"
#include "Iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference> {
 protected:
  Iterator current_;

 public:
  typedef Iterator iterator_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;
  typedef
      typename iterator_traits<Iterator>::iterator_category iterator_category;

  reverse_iterator() : current_(Iterator()){};
  explicit reverse_iterator(iterator_type x) : current_(iterator_type()){};
  reverse_iterator(const reverse_iterator& u) : current_(){};  // TODO base
  ~reverse_iterator(){};

  reverse_iterator& operator=(const reverse_iterator& rhs) {
    if (this != &rhs) {
      current_ = rhs.current_;
    }
    return *this;
  };  // TODO

  reference operator*() const {
    Iterator tmp = current_;
    return *--tmp;
  };

  pointer operator->() const { return &(operator*()); };

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current_ - n);
  };

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current_ + n);
  };

  reverse_iterator& operator+=(difference_type n) {
    current_ -= n;
    return *this;
  };

  reverse_iterator& operator-=(difference_type n) {
    current_ += n;
    return *this;
  };

  reverse_iterator& operator++() {
    --current_;
    return *this;
  };

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current_;
    return tmp;
  }

  reverse_iterator& operator--() {
    ++current_;
    return *this;
  };

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current_;
    return tmp;
  }

  reference operator[](difference_type n) const { return base()[-n - 1]; };

  iterator_type base() const { return current_; }
};

template <class Iterator1, class Iterator2>
bool operator==(const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator!=(const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() != rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator>(const std::reverse_iterator<Iterator1>& lhs,
               const std::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() > rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator<(const std::reverse_iterator<Iterator1>& lhs,
               const std::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() < rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator>=(const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() >= rhs.base();
};

template <class Iterator1, class Iterator2>
bool operator<=(const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() <= rhs.base();
};

template <class Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& it) {
  return reverse_iterator<Iterator>(it.base() - n);
};

template <class Iterator>
reverse_iterator<Iterator> operator-(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& it) {
  return reverse_iterator<Iterator>(it.base() + n);
};

}  // namespace ft

#endif /* ************************************************ REVERSE_ITERATOR_H \
        */