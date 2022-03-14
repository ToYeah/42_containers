#include <gtest/gtest.h>

#include <iterator>

#include "Iterator_traits.hpp"

// Same behavior
TEST(Iterator_traits, FromIntIterator) {
  typedef std::iterator_traits<std::vector<int>::iterator> std_traits;
  typedef ft::iterator_traits<std::vector<int>::iterator> ft_traits;

  EXPECT_EQ(typeid(std_traits::difference_type),
            typeid(ft_traits::difference_type));
  EXPECT_EQ(typeid(std_traits::value_type), typeid(ft_traits::value_type));
  EXPECT_EQ(typeid(std_traits::pointer), typeid(ft_traits::pointer));
  EXPECT_EQ(typeid(std_traits::reference), typeid(ft_traits::reference));
  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}

TEST(Iterator_traits, FromIntPointer) {
  typedef std::iterator_traits<int*> std_traits;
  typedef ft::iterator_traits<int*> ft_traits;

  EXPECT_EQ(typeid(std_traits::difference_type),
            typeid(ft_traits::difference_type));
  EXPECT_EQ(typeid(std_traits::value_type), typeid(ft_traits::value_type));
  EXPECT_EQ(typeid(std_traits::pointer), typeid(ft_traits::pointer));
  EXPECT_EQ(typeid(std_traits::reference), typeid(ft_traits::reference));
  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}

TEST(Iterator_traits, FromConstIntPointer) {
  typedef std::iterator_traits<const int*> std_traits;
  typedef ft::iterator_traits<const int*> ft_traits;

  EXPECT_EQ(typeid(std_traits::difference_type),
            typeid(ft_traits::difference_type));
  EXPECT_EQ(typeid(std_traits::value_type), typeid(ft_traits::value_type));
  EXPECT_EQ(typeid(std_traits::pointer), typeid(ft_traits::pointer));
  EXPECT_EQ(typeid(std_traits::reference), typeid(ft_traits::reference));
  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}

TEST(Iterator_traits, FromStringIterator) {
  typedef std::iterator_traits<std::vector<std::string>::iterator> std_traits;
  typedef ft::iterator_traits<std::vector<std::string>::iterator> ft_traits;

  EXPECT_EQ(typeid(std_traits::difference_type),
            typeid(ft_traits::difference_type));
  EXPECT_EQ(typeid(std_traits::value_type), typeid(ft_traits::value_type));
  EXPECT_EQ(typeid(std_traits::pointer), typeid(ft_traits::pointer));
  EXPECT_EQ(typeid(std_traits::reference), typeid(ft_traits::reference));
  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}

TEST(Iterator_traits, FromStringPointer) {
  typedef std::iterator_traits<std::string*> std_traits;
  typedef ft::iterator_traits<std::string*> ft_traits;

  EXPECT_EQ(typeid(std_traits::difference_type),
            typeid(ft_traits::difference_type));
  EXPECT_EQ(typeid(std_traits::value_type), typeid(ft_traits::value_type));
  EXPECT_EQ(typeid(std_traits::pointer), typeid(ft_traits::pointer));
  EXPECT_EQ(typeid(std_traits::reference), typeid(ft_traits::reference));
  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}

TEST(Iterator_traits, FromConstStringPointer) {
  typedef std::iterator_traits<const std::string*> std_traits;
  typedef ft::iterator_traits<const std::string*> ft_traits;

  EXPECT_EQ(typeid(std_traits::difference_type),
            typeid(ft_traits::difference_type));
  EXPECT_EQ(typeid(std_traits::value_type), typeid(ft_traits::value_type));
  EXPECT_EQ(typeid(std_traits::pointer), typeid(ft_traits::pointer));
  EXPECT_EQ(typeid(std_traits::reference), typeid(ft_traits::reference));
  EXPECT_EQ(typeid(std_traits::iterator_category),
            typeid(ft_traits::iterator_category));
}
