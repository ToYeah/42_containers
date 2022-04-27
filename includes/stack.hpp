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
  container_type c;

 public:
  explicit stack(const Container& cont = Container()) : c(cont) {}

  ~stack() {}

  stack& operator=(const stack& other) {
    if (this != &other) {
      c = other.c;
    }
    return *this;
  }

  // Element access--------------------------------------

  value_type& top() { return c.back(); }

  const value_type& top() const { return c.back(); }

  // Capacity--------------------------------------------

  bool empty() const { return size() == 0; }

  size_type size() const { return c.size(); };

  // Modifiers-------------------------------------------

  void push(const value_type& val) { c.push_back(val); }

  void pop() { c.pop_back(); };

  // Comparison------------------------------------------

  template <class T1, class _C1>
  friend bool operator==(const stack<T1, _C1>& lhs, const stack<T1, _C1>& rhs);

  template <class T1, class _C1>
  friend bool operator<(const stack<T1, _C1>& lhs, const stack<T1, _C1>& rhs);
};

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs > rhs);
}

template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return rhs < lhs;
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif /* *********************************************************** STACK_H \
        */