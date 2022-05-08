#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <limits>

#include "AVLTree.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<pair<const Key, T> > >
class map {
 private:
  typedef AVLTree<Key, T, Compare, Allocator> avl_tree;

 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename avl_tree::tree_iterator iterator;
  typedef typename avl_tree::const_tree_iterator const_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class map;

   protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

 public:
  avl_tree tree;
  allocator_type allocator_;
  Compare comp_;

 public:
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : tree(avl_tree(comp, alloc)), allocator_(alloc), comp_(comp) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : tree(avl_tree(comp, alloc)), allocator_(alloc), comp_(comp) {
    insert(first, last);
  };

  map(const map& src) { *this = src; };

  ~map(){};

  map& operator=(const map& rhs) {
    if (this != &rhs) {
      tree = rhs.tree;
      allocator_ = rhs.allocator_;
      comp_ = rhs.comp_;
    }
    return *this;
  };

  allocator_type get_allocator() const { return allocator_; };

  pair<iterator, bool> insert(const value_type& value) {
    return tree.insertNode(value);
  }

  iterator insert(iterator position, const value_type& val) {
    iterator res = find(val.first);
    if (res != end()) return res;

    res = tree.insertNodeWithHint(position, val);
    if (res != end()) return res;

    return (tree.insertNode(val)).first;
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    for (InputIt it = first; it != last; it++) {
      tree.insertNode(*it);
    }
  }

  iterator begin() { return tree.getBeginIterator(); };
  const_iterator begin() const { return tree.getBeginIterator(); };

  iterator end() { return tree.getEndIterator(); };
  const_iterator end() const { return tree.getEndIterator(); };

  reverse_iterator rbegin() { return reverse_iterator(end()); };
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  };

  reverse_iterator rend() { return reverse_iterator(begin()); };
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  };

  bool empty() const { return tree.isEmpty(); };

  size_type size() const { return tree.size(); };

  size_type max_size() const {
    return std::min<size_type>(std::numeric_limits<difference_type>::max(),
                               tree.getMaxSize());
  };

  mapped_type& operator[](const key_type& k) {
    iterator it = tree.findData(k);
    if (it == end()) {
      it = insert(ft::make_pair(k, mapped_type())).first;
    }
    return (*it).second;
  };

  iterator find(const key_type& k) { return tree.findData(k); }

  const_iterator find(const key_type& k) const { return tree.findData(k); };

  void clear() { tree.clearTree(); };

  void erase(iterator position) { tree.deleteNode((*position).first); };

  size_type erase(const key_type& k) {
    if (tree.deleteNode(k)) {
      return 1;
    }
    return 0;
  };

  void erase(iterator first, iterator last) {
    for (iterator it = first; it != last;) {
      erase(it++);
    }
  }

  void swap(map& x) {
    tree.swap(x.tree);
    std::swap(allocator_, x.allocator_);
    std::swap(comp_, x.comp_);
  }

  key_compare key_comp() const { return key_compare(); }

  value_compare value_comp() const { return value_compare(comp_); }

  size_type count(const key_type& k) const {
    if (tree.findNode(k) != NULL) {
      return 1;
    }
    return 0;
  }

  iterator lower_bound(const key_type& k) {
    return iterator(tree.findLowerBoundNode(k));
  }
  const_iterator lower_bound(const key_type& k) const {
    return const_iterator(tree.findLowerBoundNode(k));
  }
  iterator upper_bound(const key_type& k) {
    return iterator(tree.findUpperBoundNode(k));
  }

  const_iterator upper_bound(const key_type& k) const {
    return const_iterator(tree.findUpperBoundNode(k));
  }

  pair<iterator, iterator> equal_range(const key_type& k) {
    return ft::make_pair(lower_bound(k), upper_bound(k));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
    return ft::make_pair(lower_bound(k), upper_bound(k));
  }
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return lhs.size() == rhs.size() &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs > rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs,
          ft::map<Key, T, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft

#endif /* ************************************************************* MAP_H \
        */