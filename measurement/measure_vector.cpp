#include <list>
#include <vector>

#include "Measurement.hpp"
#include "vector.hpp"

int main() {
  std::list<int> lst;
  for (size_t i = 0; i < 10000; i++) {
    lst.push_back(i * i);
  }

  {
    // TEST: Constructor Default
    MEASUREMENT(LOOP(TEST::vector<int> vec1;));
  }

  {
    // TEST: Constructor Allocator
    std::allocator<int> alloc;
    MEASUREMENT(LOOP(TEST::vector<int> vec1(alloc)));
  }

  {
    // TEST: Constructor Copy
    TEST::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    MEASUREMENT(LOOP(TEST::vector<int> vec1(vec)));
  }

  {
    // TEST: Constructor Range
    MEASUREMENT(TEST::vector<int> vec(lst.begin(), lst.end()));
  };

  {
    // TEST: Constructor Size Value
    MEASUREMENT(TEST::vector<int> vec(10000, 10000));
  }
}