#include <list>
#include <map>

#include "Measurement.hpp"
#include "map.hpp"

typedef TEST::map<int, std::string> t_map;
typedef TEST::pair<int, std::string> pair;

int main() {
  std::list<pair> lst;
  for (size_t i = 0; i < 10001; i++) {
    lst.push_back(TEST::make_pair(i, "hello"));
  }

  {
    // TEST: Constructor Default
    MEASUREMENT(LOOP(t_map map));
  }

  {
    // TEST: Constructor Range
    MEASUREMENT(t_map map(lst.begin(), lst.end()));
  }

  {
    // TEST: Constructor Copy
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(t_map map_cp(map));
  }

  {
    // TEST: Operator=
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(t_map map_cp = map);
  }

  {
    // TEST: begin()
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.begin()));
  }

  {
    // TEST: begin() const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.begin()));
  }

  {
    // TEST: end()
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.end()));
  }

  {
    // TEST: end() const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.end()));
  }

  {
    // TEST: rbegin()
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.rbegin()));
  }

  {
    // TEST: rbegin() const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.rbegin()));
  }

  {
    // TEST: rend()
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.rend()));
  }

  {
    // TEST: rend() const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.rend()));
  }

  {
    // TEST: empty true
    t_map map;
    MEASUREMENT(LOOP(map.empty()));
  }

  {
    // TEST: empty false
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.empty()));
  }

  {
    // TEST: size
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.size()));
  }

  {
    // TEST: max_size
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.max_size()));
  }

  {
    // TEST: operator[]
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map[i]; });
  }

  {
    // TEST: insert value
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000;
                     i++) { map.insert(pair(i + 1000, "hello")); });
  }

  {
    // TEST: insert Position val
    t_map map;
    MEASUREMENT(for (size_t i = 0; i < 10000;
                     i++) { map.insert(map.begin(), pair(i, "hello")); });
  }

  {
    // TEST: insert Range
    t_map map;
    MEASUREMENT(map.insert(lst.begin(), lst.end()));
  }

  {
    // TEST: erase position
    t_map map(lst.begin(), lst.end());
    for (size_t i = 0; i < 100; i++) {
      map.insert(pair(i + 10000, "hello"));
    }
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.erase(map.begin()); });
  }

  {
    // TEST: erase key
    t_map map(lst.begin(), lst.end());
    for (size_t i = 0; i < 100; i++) {
      map.insert(pair(i + 10000, "hello"));
    }
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.erase(i); });
  }

  {
    // TEST: erase range
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(map.erase(map.begin(), map.end()););
  }

  {
    // TEST: swap
    t_map map(lst.begin(), lst.end());
    t_map map2(lst.begin(), lst.end());
    map.swap(map2);
  }

  {
    // TEST: clear
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(map.clear());
  }

  {
    // TEST: key_comp
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.key_comp()));
  }

  {
    // TEST: value_comp
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.value_comp()));
  }

  {
    // TEST: find
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.find(i); });
  }

  {
    // TEST: find const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.find(i); });
  }

  {
    // TEST: count
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.count(i); });
  }

  {
    // TEST: lower_bound
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.lower_bound(i); });
  }

  {
    // TEST: lower_bound const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.lower_bound(i); });
  }

  {
    // TEST: upper_bound
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.upper_bound(i); });
  }

  {
    // TEST: upper_bound const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.upper_bound(i); });
  }

  {
    // TEST: equal_range
    t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.equal_range(i); });
  }

  {
    // TEST: equal_range const
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { map.equal_range(i); });
  }

  {
    // TEST: get_allocator
    const t_map map(lst.begin(), lst.end());
    MEASUREMENT(LOOP(map.get_allocator()));
  }
}