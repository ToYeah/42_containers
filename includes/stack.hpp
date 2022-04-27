#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >

class stack {
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;

 protected:
  Container c;

 public:
  explicit stack(const Container& cont = Container()) : c(cont) {}

  ~stack() {}

  stack& operator=(const stack& other) {
    if (this != &other) {
      c = other.c;
    }
    return *this;
  }
};

}  // namespace ft

#endif /* *********************************************************** STACK_H \
        */