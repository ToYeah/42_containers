
#include <list>
#include <map>
#include <memory>
#include <string>

#include "map.hpp"

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

#define EXPECT_TRUE(i) i

int main() {
  ft_map_type ft_map;
  std_map_type std_map;

  make_map(ft_map, std_map);

  EXPECT_TRUE(equal(ft_map, std_map));

  std_map_type std_erase;
  ft_map_type ft_erase;
  for (size_t i = 1; i < 2; i++) {
    std_erase.insert(std::make_pair(i * i, "hello"));
    ft_erase.insert(ft::make_pair(i * i, "hello"));
  }

  std::cout << ft_map.size() << std::endl;

  ft_map.erase(ft_erase.begin(), ft_erase.end());
  std_map.erase(std_erase.begin(), std_erase.end());
  EXPECT_TRUE(equal(ft_map, std_map));
}