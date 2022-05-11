#include "vector.hpp"

#include <gtest/gtest.h>

#include <list>
#include <memory>
#include <vector>

template <class T>
bool equal(const ft::vector<T>& ft, const std::vector<T>& std) {
  if (ft.size() != std.size() || ft.empty() != std.empty()) return false;
  for (size_t i = 0; i < ft.size(); i++) {
    if (ft[i] != std[i]) return false;
  }
  return true;
}

TEST(vector, defaultConstructor) {
  std::vector<int> std_vec;
  ft::vector<int> ft_vec;
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, allocConstructor) {
  std::allocator<int> alloc;
  std::vector<int> std_vec(alloc);
  ft::vector<int> ft_vec(alloc);
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, FillConstructor) {
  std::vector<int> std_vec(100, 10);
  ft::vector<int> ft_vec(100, 10);
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, RangeConstructor) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, CopyConstructor) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());
  EXPECT_TRUE(equal(ft_vec, std_vec));

  std::vector<int> std_vec2(std_vec);
  ft::vector<int> ft_vec2(ft_vec);
  EXPECT_TRUE(equal(ft_vec2, std_vec2));
}

TEST(vector, equalOperator) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());
  EXPECT_TRUE(equal(ft_vec, std_vec));

  std::vector<int> std_vec2;
  ft::vector<int> ft_vec2;
  std_vec2 = std_vec;
  ft_vec2 = ft_vec;
  EXPECT_TRUE(equal(ft_vec2, std_vec2));
  EXPECT_TRUE(ft_vec == ft_vec2);
  ft_vec.pop_back();
  EXPECT_FALSE(ft_vec == ft_vec2);
}

TEST(vector, begin) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::iterator std_it = std_vec.begin();
  ft::vector<int>::iterator ft_it = ft_vec.begin();
  EXPECT_TRUE(*std_it == *ft_it);
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  *std_it = 20000;
  *ft_it = 20000;
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, beginConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::const_iterator std_it = std_vec.begin();
  ft::vector<int>::const_iterator ft_it = ft_vec.begin();
  EXPECT_TRUE(*std_it == *ft_it);
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
}

TEST(vector, end) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::iterator std_it = std_vec.end();
  ft::vector<int>::iterator ft_it = ft_vec.end();
  std_it--;
  ft_it--;
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  *std_it = 20000;
  *ft_it = 20000;
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, endConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::const_iterator std_it = std_vec.end();
  ft::vector<int>::const_iterator ft_it = ft_vec.end();
  std_it--;
  ft_it--;
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, rbegin) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::reverse_iterator std_it = std_vec.rbegin();
  ft::vector<int>::reverse_iterator ft_it = ft_vec.rbegin();
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  *std_it = 20000;
  *ft_it = 20000;
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, rbeginConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::const_reverse_iterator std_it = std_vec.rbegin();
  ft::vector<int>::const_reverse_iterator ft_it = ft_vec.rbegin();
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it++;
  ft_it++;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, rend) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::reverse_iterator std_it = std_vec.rend();
  ft::vector<int>::reverse_iterator ft_it = ft_vec.rend();
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  *std_it = 20000;
  *ft_it = 20000;
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, rendConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::const_reverse_iterator std_it = std_vec.rend();
  ft::vector<int>::const_reverse_iterator ft_it = ft_vec.rend();
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  std_it--;
  ft_it--;
  EXPECT_TRUE(*std_it == *ft_it);
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, size) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(std_vec.size() == ft_vec.size());

  std::vector<int> std_vec2;
  ft::vector<int> ft_vec2;

  EXPECT_TRUE(std_vec2.size() == ft_vec2.size());
}

TEST(vector, resize) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std_vec.resize(100, 10);
  ft_vec.resize(100, 10);
  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.resize(1000, 10);
  ft_vec.resize(1000, 10);
  EXPECT_TRUE(equal(ft_vec, std_vec));

  std::vector<int> std_vec2;
  ft::vector<int> ft_vec2;

  EXPECT_TRUE(equal(ft_vec, std_vec));
  std_vec2.resize(1000, 10);
  ft_vec2.resize(1000, 10);
}

TEST(vector, empty) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(ft_vec.empty() == std_vec.empty());

  std::vector<int> std_vec2;
  ft::vector<int> ft_vec2;

  EXPECT_TRUE(ft_vec.empty() == std_vec.empty());
}

TEST(vector, AccessOperator) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec[1] == std_vec[1]);
  EXPECT_TRUE(ft_vec[2] == std_vec[2]);
  EXPECT_TRUE(ft_vec[3] == std_vec[3]);

  ft_vec[1] = std_vec[1] = ft_vec[2] = std_vec[2] = ft_vec[3] = std_vec[3] =
      100000;

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, AccessOperatorConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec[1] == std_vec[1]);
  EXPECT_TRUE(ft_vec[2] == std_vec[2]);
  EXPECT_TRUE(ft_vec[3] == std_vec[3]);

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, at) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec.at(1) == std_vec.at(1));
  EXPECT_TRUE(ft_vec.at(2) == std_vec.at(2));
  EXPECT_TRUE(ft_vec.at(3) == std_vec.at(3));

  ft_vec.at(1) = std_vec.at(1) = ft_vec.at(2) = std_vec.at(2) = ft_vec.at(3) =
      std_vec.at(3) = 100000;

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, atConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec.at(1) == std_vec.at(1));
  EXPECT_TRUE(ft_vec.at(2) == std_vec.at(2));
  EXPECT_TRUE(ft_vec.at(3) == std_vec.at(3));

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, front) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec.front() == std_vec.front());

  ft_vec.front() = 100000;
  std_vec.front() = 100000;
  EXPECT_TRUE(ft_vec.front() == std_vec.front());
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, frontConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec.front() == std_vec.front());

  ft_vec.front() = 100000;
  std_vec.front() = 100000;
  EXPECT_TRUE(ft_vec.front() == std_vec.front());
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, back) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec.back() == std_vec.back());

  ft_vec.back() = 100000;
  std_vec.back() = 100000;
  EXPECT_TRUE(ft_vec.back() == std_vec.back());
  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, backConst) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  const std::vector<int> std_vec(lst.begin(), lst.end());
  const ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  EXPECT_TRUE(ft_vec.back() == std_vec.back());

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, assignRange) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec;
  ft::vector<int> ft_vec;

  std_vec.push_back(1);
  ft_vec.push_back(2);

  EXPECT_FALSE(equal(ft_vec, std_vec));

  std_vec.assign(lst.begin(), lst.end());
  ft_vec.assign(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.assign(++lst.begin(), --lst.end());
  ft_vec.assign(++lst.begin(), --lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  std_vec.assign(++(++lst.begin()), lst.end());
  ft_vec.assign(++(++lst.begin()), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, assignSizeValue) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec;
  ft::vector<int> ft_vec;

  std_vec.push_back(1);
  ft_vec.push_back(2);

  EXPECT_FALSE(equal(ft_vec, std_vec));

  std_vec.assign(100, 20);
  ft_vec.assign(100, 20);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.assign(10, 10);
  ft_vec.assign(10, 10);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  std_vec.assign(50, 70);
  ft_vec.assign(50, 70);

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, push_back) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec;
  ft::vector<int> ft_vec;

  std_vec.push_back(1);
  ft_vec.push_back(1);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.push_back(1);
  ft_vec.push_back(1);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.assign(10, 20);
  ft_vec.assign(10, 20);

  std_vec.push_back(1);
  ft_vec.push_back(1);

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, pop_back) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.pop_back();
  ft_vec.pop_back();

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.pop_back();
  ft_vec.pop_back();

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std::vector<int> std_vec2(lst.begin(), ++lst.begin());
  ft::vector<int> ft_vec2(lst.begin(), ++lst.begin());

  EXPECT_TRUE(equal(ft_vec2, std_vec2));

  std_vec2.pop_back();
  ft_vec2.pop_back();

  EXPECT_TRUE(equal(ft_vec2, std_vec2));
}

TEST(vector, insertPosValue) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.insert(std_vec.begin(), 100000);
  ft_vec.insert(ft_vec.begin(), 100000);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.insert(--std_vec.end(), 1002000);
  ft_vec.insert(--ft_vec.end(), 1002000);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  std_vec.insert(std_vec.begin(), 1002000);
  ft_vec.insert(ft_vec.begin(), 1002000);

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, insertPosSizeValue) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.insert(std_vec.begin(), 5, 100000);
  ft_vec.insert(ft_vec.begin(), 5, 100000);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.insert(--std_vec.end(), 10, 1002000);
  ft_vec.insert(--ft_vec.end(), 10, 1002000);

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  std_vec.insert(std_vec.begin(), 15, 1002000);
  ft_vec.insert(ft_vec.begin(), 15, 1002000);

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, insertPosRange) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.insert(std_vec.begin(), lst.begin(), lst.end());
  ft_vec.insert(ft_vec.begin(), lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.insert(--std_vec.end(), lst.begin(), lst.end());
  ft_vec.insert(--ft_vec.end(), lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  std_vec.insert(std_vec.begin(), lst.begin(), lst.end());
  ft_vec.insert(ft_vec.begin(), lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, erasePos) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::iterator std_it;
  ft::vector<int>::iterator ft_it;

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_it = std_vec.erase(std_vec.begin());
  ft_it = ft_vec.erase(ft_vec.begin());

  EXPECT_TRUE(equal(ft_vec, std_vec));
  EXPECT_TRUE(*ft_it == *std_it);

  std_it = std_vec.erase(std_vec.begin());
  ft_it = ft_vec.erase(ft_vec.begin());

  EXPECT_TRUE(equal(ft_vec, std_vec));
  EXPECT_TRUE(*ft_it == *std_it);

  std_it = std_vec.erase(--std_vec.end());
  ft_it = ft_vec.erase(--ft_vec.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));
  EXPECT_TRUE(*ft_it == *std_it);
}

TEST(vector, eraseRange) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  std::vector<int>::iterator std_it;
  ft::vector<int>::iterator ft_it;

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_it = std_vec.erase(std_vec.begin(), ++(++(++(++std_vec.begin()))));
  ft_it = ft_vec.erase(ft_vec.begin(), ++(++(++(++ft_vec.begin()))));

  EXPECT_TRUE(equal(ft_vec, std_vec));
  EXPECT_TRUE(*ft_it == *std_it);

  std_it = std_vec.erase(std_vec.begin(), ++(++(++(++std_vec.begin()))));
  ft_it = ft_vec.erase(ft_vec.begin(), ++(++(++(++ft_vec.begin()))));

  EXPECT_TRUE(equal(ft_vec, std_vec));
  EXPECT_TRUE(*ft_it == *std_it);

  std_it = std_vec.erase(std_vec.begin(), --std_vec.end());
  ft_it = ft_vec.erase(ft_vec.begin(), --ft_vec.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));
  EXPECT_TRUE(*ft_it == *std_it);
}

TEST(vector, swap) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::list<int> lst2;
  for (size_t i = 0; i < 100; i++) {
    lst2.push_back(i + 100);
  }

  ft::vector<int> ft_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec2(lst2.begin(), lst2.end());

  ft::vector<int> ft_vec_cp = ft_vec;
  ft::vector<int> ft_vec2_cp = ft_vec2;

  ft_vec.swap(ft_vec2);

  EXPECT_EQ(ft_vec, ft_vec2_cp);
  EXPECT_EQ(ft_vec2, ft_vec_cp);

  ft_vec.swap(ft_vec2);

  EXPECT_EQ(ft_vec, ft_vec_cp);
  EXPECT_EQ(ft_vec2, ft_vec2_cp);
}

TEST(vector, clear) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::vector<int> std_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec(lst.begin(), lst.end());

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  EXPECT_TRUE(equal(ft_vec, std_vec));

  std_vec.clear();
  ft_vec.clear();

  EXPECT_TRUE(equal(ft_vec, std_vec));
}

TEST(vector, swapNonMember) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::list<int> lst2;
  for (size_t i = 0; i < 100; i++) {
    lst2.push_back(i + 100);
  }

  ft::vector<int> ft_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec2(lst2.begin(), lst2.end());

  ft::vector<int> ft_vec_cp = ft_vec;
  ft::vector<int> ft_vec2_cp = ft_vec2;

  ft::swap(ft_vec, ft_vec2);

  EXPECT_EQ(ft_vec, ft_vec2_cp);
  EXPECT_EQ(ft_vec2, ft_vec_cp);

  ft::swap(ft_vec, ft_vec2);

  EXPECT_EQ(ft_vec, ft_vec_cp);
  EXPECT_EQ(ft_vec2, ft_vec2_cp);
}

TEST(vector, relationalOperator) {
  std::list<int> lst;
  for (size_t i = 0; i < 100; i++) {
    lst.push_back(i);
  }

  std::list<int> lst2;
  for (size_t i = 0; i < 100; i++) {
    lst2.push_back(i + 100);
  }

  ft::vector<int> ft_vec(lst.begin(), lst.end());
  ft::vector<int> ft_vec2(lst2.begin(), lst2.end());

  EXPECT_TRUE(ft_vec == ft_vec);
  EXPECT_FALSE(ft_vec != ft_vec);
  EXPECT_TRUE(ft_vec == ft_vec);
  EXPECT_TRUE(ft_vec != ft_vec2);
  EXPECT_TRUE(ft_vec < ft_vec2);
  EXPECT_TRUE(ft_vec2 > ft_vec);
  EXPECT_TRUE(ft_vec <= ft_vec2);
  EXPECT_TRUE(ft_vec2 >= ft_vec);
  EXPECT_TRUE(ft_vec <= ft_vec);
  EXPECT_TRUE(ft_vec >= ft_vec);
}

TEST(vector, get_allocator) {
  {
    ft::vector<int> ft_vec;
    std::allocator<int> alloc;
    EXPECT_EQ(alloc, ft_vec.get_allocator());
  }
  {
    ft::vector<float> ft_vec;
    std::allocator<float> alloc;
    EXPECT_EQ(alloc, ft_vec.get_allocator());
  }
}