#include "stack.hpp"

#include <gtest/gtest.h>

#include <list>
#include <memory>
#include <stack>

template <class T>
bool equal(const ft::stack<T>& ft, const std::stack<T>& std) {
  ft::stack<T> ft_cp(ft);
  std::stack<T> std_cp(std);
  if (ft_cp.size() != std_cp.size() || ft_cp.empty() != std_cp.empty())
    return false;
  while (ft_cp.size() && std_cp.size()) {
    if (ft_cp.top() != std_cp.top()) {
      return false;
    }
    ft_cp.pop();
    std_cp.pop();
  }

  return true;
}

TEST(stack, defaultConstructor) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;
  EXPECT_TRUE(equal(ft_sta, std_sta));
}

TEST(stack, empty) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;

  EXPECT_EQ(ft_sta.empty(), std_sta.empty());
  std_sta.push(1);
  ft_sta.push(1);
  EXPECT_TRUE(equal(ft_sta, std_sta));
}

TEST(stack, size) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;

  EXPECT_EQ(ft_sta.size(), std_sta.size());
  std_sta.push(1);
  ft_sta.push(1);
  EXPECT_EQ(ft_sta.size(), std_sta.size());
  std_sta.push(1);
  ft_sta.push(1);
  std_sta.push(1);
  ft_sta.push(1);
  std_sta.push(1);
  ft_sta.push(1);
  std_sta.push(1);
  ft_sta.push(1);
  std_sta.push(1);
  ft_sta.push(1);
  EXPECT_EQ(ft_sta.size(), std_sta.size());

  EXPECT_TRUE(equal(ft_sta, std_sta));
}

TEST(stack, top) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;

  std_sta.push(1);
  ft_sta.push(1);
  EXPECT_EQ(ft_sta.top(), std_sta.top());
  std_sta.push(2);
  ft_sta.push(2);
  EXPECT_EQ(ft_sta.top(), std_sta.top());
  std_sta.push(3);
  ft_sta.push(3);
  EXPECT_EQ(ft_sta.top(), std_sta.top());

  EXPECT_TRUE(equal(ft_sta, std_sta));
}

TEST(stack, topConst) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;

  std_sta.push(1);
  ft_sta.push(1);
  {
    const std::stack<int> std_sta_cp(std_sta);
    const ft::stack<int> ft_sta_cp(ft_sta);
    EXPECT_EQ(ft_sta_cp.top(), std_sta_cp.top());
  }

  std_sta.push(2);
  ft_sta.push(2);
  {
    const std::stack<int> std_sta_cp(std_sta);
    const ft::stack<int> ft_sta_cp(ft_sta);
    EXPECT_EQ(ft_sta_cp.top(), std_sta_cp.top());
  }

  std_sta.push(3);
  ft_sta.push(3);
  {
    const std::stack<int> std_sta_cp(std_sta);
    const ft::stack<int> ft_sta_cp(ft_sta);
    EXPECT_EQ(ft_sta_cp.top(), std_sta_cp.top());
  }
}

TEST(stack, push) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;

  for (size_t i = 0; i < 1000; i++) {
    std_sta.push(i);
    ft_sta.push(i);
    EXPECT_TRUE(equal(ft_sta, std_sta));
  }
}

TEST(stack, pop) {
  std::stack<int> std_sta;
  ft::stack<int> ft_sta;

  for (size_t i = 0; i < 1000; i++) {
    std_sta.push(i);
    ft_sta.push(i);
  }

  for (size_t i = 0; i < 1000; i++) {
    std_sta.pop();
    ft_sta.pop();
    EXPECT_TRUE(equal(ft_sta, std_sta));
  }
}

TEST(stack, RelationalOperator) {
  ft::stack<int> ft_sta;
  ft::stack<int> ft_sta2;
  ft::stack<int> ft_sta3;

  for (size_t i = 0; i < 1000; i++) {
    ft_sta.push(i);
    ft_sta2.push(i);
  }

  ft_sta2.push(100000);

  EXPECT_TRUE(ft_sta == ft_sta);
  EXPECT_TRUE(ft_sta != ft_sta2);
  EXPECT_TRUE(ft_sta < ft_sta2);
  EXPECT_TRUE(ft_sta2 > ft_sta);
  EXPECT_TRUE(ft_sta <= ft_sta2);
  EXPECT_TRUE(ft_sta2 >= ft_sta);
  EXPECT_TRUE(ft_sta <= ft_sta);
  EXPECT_TRUE(ft_sta >= ft_sta);
}
