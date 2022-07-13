#include "map.hpp"

#include <gtest/gtest.h>

#include <list>
#include <map>
#include <memory>
#include <string>

typedef ft::pair<int, std::string> ft_pair;
typedef std::pair<int, std::string> std_pair;

typedef ft::map<int, std::string> ft_map_type;
typedef std::map<int, std::string> std_map_type;

template <class T, class U>
bool equal(const ft::map<T, U>& ft, const std::map<T, U>& std) {
  if (ft.size() != std.size() || ft.empty() != std.empty()) return false;
  typename ft::map<T, U>::const_iterator ft_it = ft.begin();
  typename std::map<T, U>::const_iterator std_it = std.begin();
  while (ft_it != ft.end() && std_it != std.end()) {
    bool first_comp = (*ft_it).first == (*std_it).first;
    bool second_comp = (*ft_it).second == (*std_it).second;
    if (!first_comp || !second_comp) {
      return false;
    }
    ft_it++;
    std_it++;
  }

  return true;
}

template <class T, class U>
bool equal(const ft::pair<T, U>& ft, const std::pair<T, U>& std) {
  if (ft.first == std.first && ft.second == std.second) return true;
  return false;
}

void make_map(ft_map_type& ft, std_map_type& std) {
  for (size_t i = 0; i < 1000; i++) {
    std.insert(std::make_pair(i, "hello"));
    ft.insert(ft::make_pair(i, "hello"));
  }
}

TEST(map, defaultConstructor) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.insert(ft_pair(1, "nice"));
  std_map.insert(std_pair(1, "nice"));

  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, RangeConstructor) {
  std::list<std_pair> std_lst;
  std::list<ft_pair> ft_lst;
  for (size_t i = 0; i < 1000; i++) {
    std_lst.push_back(std::make_pair(i, "hello"));
    ft_lst.push_back(ft::make_pair(i, "hello"));
  }

  std_map_type std_map(std_lst.begin(), std_lst.end());
  ft_map_type ft_map(ft_lst.begin(), ft_lst.end());

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.insert(ft_pair(1111, "nice"));
  std_map.insert(std_pair(1111, "nice"));

  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, CopyConstructor) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  std_map_type std_map_cp(std_map);
  ft_map_type ft_map_cp(ft_map);

  EXPECT_TRUE(equal(ft_map_cp, std_map_cp));
}

TEST(map, AssignOperator) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  std_map_type std_map_cp;
  ft_map_type ft_map_cp;

  std_map_cp = std_map;
  ft_map_cp = ft_map;

  EXPECT_TRUE(equal(ft_map_cp, std_map_cp));
}

TEST(map, begin) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  std_map_type::iterator std_it = std_map.begin();
  ft_map_type::iterator ft_it = ft_map.begin();

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, Constbegin) {
  std_map_type std_map_old;
  ft_map_type ft_map_old;
  make_map(ft_map_old, std_map_old);
  const std_map_type std_map(std_map_old);
  const ft_map_type ft_map(ft_map_old);

  EXPECT_TRUE(equal(ft_map, std_map));

  std_map_type::const_iterator std_it = std_map.begin();
  ft_map_type::const_iterator ft_it = ft_map.begin();

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, end) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  std_map_type::iterator std_it = std_map.end();
  ft_map_type::iterator ft_it = ft_map.end();

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));
  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, ConstEnd) {
  std_map_type std_map_old;
  ft_map_type ft_map_old;
  make_map(ft_map_old, std_map_old);
  const std_map_type std_map(std_map_old);
  const ft_map_type ft_map(ft_map_old);

  EXPECT_TRUE(equal(ft_map, std_map));

  std_map_type::const_iterator std_it = std_map.end();
  ft_map_type::const_iterator ft_it = ft_map.end();

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));
  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, rbegin) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  std_map_type::reverse_iterator std_it = std_map.rbegin();
  ft_map_type::reverse_iterator ft_it = ft_map.rbegin();

  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, Constrbegin) {
  std_map_type std_map_old;
  ft_map_type ft_map_old;
  make_map(ft_map_old, std_map_old);
  const std_map_type std_map(std_map_old);
  const ft_map_type ft_map(ft_map_old);

  EXPECT_TRUE(equal(ft_map, std_map));

  std_map_type::const_reverse_iterator std_it = std_map.rbegin();
  ft_map_type::const_reverse_iterator ft_it = ft_map.rbegin();

  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
  std_it++;
  ft_it++;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, rend) {
  std_map_type std_map;
  ft_map_type ft_map;
  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  std_map_type::reverse_iterator std_it = std_map.rend();
  ft_map_type::reverse_iterator ft_it = ft_map.rend();

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, Constrend) {
  std_map_type std_map_old;
  ft_map_type ft_map_old;
  make_map(ft_map_old, std_map_old);
  const std_map_type std_map(std_map_old);
  const ft_map_type ft_map(ft_map_old);

  EXPECT_TRUE(equal(ft_map, std_map));

  std_map_type::const_reverse_iterator std_it = std_map.rend();
  ft_map_type::const_reverse_iterator ft_it = ft_map.rend();

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));

  std_it--;
  ft_it--;

  EXPECT_TRUE(equal(*ft_it, *std_it));
}

TEST(map, empty) {
  std_map_type std_map;
  ft_map_type ft_map;

  EXPECT_EQ(ft_map.empty(), std_map.empty());

  make_map(ft_map, std_map);

  EXPECT_EQ(ft_map.empty(), std_map.empty());
}

TEST(map, size) {
  ft_map_type ft_map;
  std_map_type std_map;

  EXPECT_EQ(ft_map.size(), std_map.size());

  make_map(ft_map, std_map);

  EXPECT_EQ(ft_map.size(), std_map.size());

  ft_map.insert(ft::make_pair(1111, "a"));
  std_map.insert(std::make_pair(1111, "a"));

  EXPECT_EQ(ft_map.size(), std_map.size());
}

TEST(map, AtOperator) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  for (size_t i = 0; i < 1000; i++) {
    EXPECT_TRUE(ft_map[i] == std_map[i]);
  }
  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, insert) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  ft_map.insert(ft::make_pair(1111, "hello"));
  std_map.insert(std::make_pair(1111, "hello"));

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.insert(ft::make_pair(11132, "hello"));
  std_map.insert(std::make_pair(11132, "hello"));

  EXPECT_TRUE(equal(ft_map, std_map));
  ft_map.insert(ft::make_pair(-1, "hello"));
  std_map.insert(std::make_pair(-1, "hello"));
  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, insertWithHint) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  ft_map.insert(--ft_map.end(), ft::make_pair(1111, "hello"));
  std_map.insert(--std_map.end(), std::make_pair(1111, "hello"));

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.insert(ft_map.begin(), ft::make_pair(-1, "hello"));
  std_map.insert(std_map.begin(), std::make_pair(-1, "hello"));
  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, rangeinsert) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  EXPECT_TRUE(equal(ft_map, std_map));

  std::list<std_pair> std_lst;
  std::list<ft_pair> ft_lst;
  for (size_t i = 0; i < 1000; i++) {
    std_lst.push_back(std::make_pair(i + 10000, "hello"));
    ft_lst.push_back(ft::make_pair(i + 10000, "hello"));
  }

  ft_map.insert(ft_lst.begin(), ft_lst.end());
  std_map.insert(std_lst.begin(), std_lst.end());
  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, erase) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  ft_map.erase(ft_map.begin());
  std_map.erase(std_map.begin());

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.erase(--ft_map.end());
  std_map.erase(--std_map.end());

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.erase(ft_map.begin());
  std_map.erase(std_map.begin());

  ft_map.erase(--ft_map.end());
  std_map.erase(--std_map.end());

  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, eraseKey) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  ft_map.erase(1);
  std_map.erase(1);

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.erase(23);
  std_map.erase(23);

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.erase(456);
  std_map.erase(456);

  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, eraseRange) {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.erase(++(++(++ft_map.begin())), ft_map.end());
  std_map.erase(++(++(++std_map.begin())), std_map.end());
  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, swap) {
  ft_map_type ft_map;
  ft_map_type ft_map2;

  for (size_t i = 0; i < 100; i++) {
    ft_map.insert(ft::make_pair(i, "hello"));
    ft_map2.insert(ft::make_pair(i + i, "hello"));
  }

  ft_map_type ft_map_cp = ft_map;
  ft_map_type ft_map2_cp = ft_map2;

  ft_map.swap(ft_map2);

  EXPECT_EQ(ft_map, ft_map2_cp);
  EXPECT_EQ(ft_map2, ft_map_cp);

  ft_map.swap(ft_map2);

  EXPECT_EQ(ft_map, ft_map_cp);
  EXPECT_EQ(ft_map2, ft_map2_cp);

  ft_map.swap(ft_map2);

  ft_map.insert(ft::make_pair(3333, "hello"));

  EXPECT_NE(ft_map, ft_map_cp);
  EXPECT_NE(ft_map, ft_map2);
  EXPECT_NE(ft_map, ft_map2_cp);
}

TEST(map, clear) {
  std_map_type std_map;
  ft_map_type ft_map;

  EXPECT_TRUE(equal(ft_map, std_map));

  make_map(ft_map, std_map);

  EXPECT_TRUE(equal(ft_map, std_map));

  ft_map.clear();
  std_map.clear();

  EXPECT_TRUE(equal(ft_map, std_map));
}

TEST(map, key_comp) {
  std_map_type std_map;
  ft_map_type ft_map;

  make_map(ft_map, std_map);

  std_map_type::key_compare std_comp = std_map.key_comp();
  ft_map_type::key_compare ft_comp = ft_map.key_comp();

  for (size_t i = 0; i < 10; i++) {
    size_t comp_val = i * i;
    EXPECT_EQ(ft_comp(i, comp_val), std_comp(i, comp_val));
    EXPECT_EQ(ft_comp(comp_val, i), std_comp(comp_val, i));
    EXPECT_EQ(ft_comp(i, i), std_comp(i, i));
  }
}
