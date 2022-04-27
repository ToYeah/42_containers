#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >

class stack {
 public:
  typedef typename Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
}

}  // namespace ft

#endif /* *********************************************************** STACK_H \
        */