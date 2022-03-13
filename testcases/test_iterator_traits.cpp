#include <gtest/gtest.h>

#include "Iterator_traits.hpp"

TEST(Iterator_traits, test) {
  typedef std::iterator_traits<int*> std_traits;
  typedef ft::iterator_traits<int*> ft_traits;

  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}