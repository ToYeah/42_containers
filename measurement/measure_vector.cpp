#include <list>
#include <vector>

#include "Measurement.hpp"
#include "vector.hpp"

int main() {
  std::list<std::string> lst;
  for (size_t i = 0; i < 10000; i++) {
    lst.push_back("hello");
  }

  {
    // TEST: Constructor Default
    MEASUREMENT(LOOP(TEST::vector<std::string> vec1;));
  }

  {
    // TEST: Fill Allocator
    MEASUREMENT(TEST::vector<std::string> vec1(10000, "hello"));
  }

  {
    // TEST: Constructor Copy
    TEST::vector<std::string> vec;
    vec.push_back("hello");
    vec.push_back("helo");
    vec.push_back("heo");
    MEASUREMENT(LOOP(TEST::vector<std::string> vec1(vec)));
  }

  {
    // TEST: Constructor Range
    MEASUREMENT(TEST::vector<std::string> vec(lst.begin(), lst.end()));
  };

  {
    // TEST: Constructor Size Value
    MEASUREMENT(TEST::vector<std::string> vec(10000, "hello"));
  }

  {// TEST: Destructor
   MEASUREMENT({ TEST::vector<std::string> vec(10000, "hello"); })}

  {
    // TEST: Operator=
    TEST::vector<std::string> vec(1000, "hello");
    TEST::vector<std::string> vec2(10000, "world");
    MEASUREMENT(vec = vec2);
  }

  {
    // TEST: begin()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.begin()))
  }

  {
    // TEST: begin() const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.begin()))
  }

  {
    // TEST: end()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.end()))
  }

  {
    // TEST: end() const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.end()))
  }

  {
    // TEST: rbegin()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.rbegin()))
  }

  {
    // TEST: rbegin() const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.rbegin()))
  }

  {
    // TEST: rend()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.rend()))
  }

  {
    // TEST: rend() const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.rend()))
  }

  {
    // TEST: size()
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.size()))
  }

  {
    // TEST: max_size()
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.max_size()))
  }

  {
    // TEST: resize()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.resize(10000)))
  }

  {
    // TEST: capacity()
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.capacity()))
  }

  {
    // TEST: empty() false
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.empty()))
  }

  {
    // TEST: empty() true
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.empty()))
  }

  {
    // TEST: reserve()
    TEST::vector<std::string> vec(1000, "hello");
    MEASUREMENT(vec.reserve(10000))
  }

  {
    // TEST: operator[]
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { vec[i]; })
  }

  {
    // TEST: operator[] const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { vec[i]; })
  }

  {
    // TEST: at()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { vec.at(i); })
  }

  {
    // TEST: at() const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(for (size_t i = 0; i < 10000; i++) { vec.at(i); })
  }

  {
    // TEST: front()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.front()))
  }

  {
    // TEST: front() const
    const TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.front()))
  }

  {
    // TEST: back()
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.back()))
  }

  {
    // TEST: back() const
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.back()))
  }

  {
    // TEST: assign Range
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(vec.assign(lst.begin(), lst.end()))
  }

  {
    // TEST: assign size value
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(vec.assign(10000, "world"))
  }

  {
    // TEST: push_back()
    TEST::vector<std::string> vec;
    MEASUREMENT(LOOP(vec.push_back("hello")))
  }

  {
    // TEST: pop_back()
    TEST::vector<std::string> vec(20000, "hello");
    MEASUREMENT(LOOP(vec.pop_back()))
  }

  {
    // TEST: insert position value
    TEST::vector<std::string> vec(1, "hello");
    MEASUREMENT(LOOP(vec.insert(vec.begin(), "hello")))
  }

  {
    // TEST: insert position size value
    TEST::vector<std::string> vec(1, "hello");
    MEASUREMENT(vec.insert(vec.begin(), 10000, "hello"))
  }

  {
    // TEST: insert position Range
    TEST::vector<std::string> vec(1, "hello");
    MEASUREMENT(vec.insert(vec.begin(), lst.begin(), lst.end()))
  }

  {
    // TEST: erase position
    TEST::vector<std::string> vec(20000, "hello");
    MEASUREMENT(LOOP(vec.erase(vec.end() - 1)))
  }

  {
    // TEST: erase Range
    TEST::vector<std::string> vec(20000, "hello");
    MEASUREMENT(vec.erase(vec.begin(), vec.end() - 100))
  }

  {
    // TEST: swap
    TEST::vector<std::string> vec(20000, "hello");
    TEST::vector<std::string> vec2(20000, "world");
    MEASUREMENT(LOOP(vec.swap(vec2)))
  }

  {
    // TEST: clear
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(vec.clear())
  }

  {
    // TEST: get_allocator
    TEST::vector<std::string> vec(10000, "hello");
    MEASUREMENT(LOOP(vec.get_allocator()))
  }

  {
    TEST::vector<std::string> vec(10000, "hello");
    TEST::vector<std::string> vec2(10000, "hello");

    // TEST: operator==
    MEASUREMENT(bool a = (vec == vec2); (void)(a))
    // TEST: operator!=
    MEASUREMENT(bool a = (vec != vec2); (void)(a))
    // TEST: operator>
    MEASUREMENT(bool a = (vec > vec2); (void)(a))
    // TEST: operator<
    MEASUREMENT(bool a = (vec < vec2); (void)(a))
    // TEST: operator>=
    MEASUREMENT(bool a = (vec >= vec2); (void)(a))
    // TEST: operator<=
    MEASUREMENT(bool a = (vec <= vec2); (void)(a))
  }

  {
    // TEST: swap()
    TEST::vector<std::string> vec(10000, "hello");
    TEST::vector<std::string> vec2(10000, "hello");
    MEASUREMENT(LOOP(swap(vec, vec2)))
  }
}