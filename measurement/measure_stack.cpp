#include <list>
#include <stack>

#include "Measurement.hpp"
#include "stack.hpp"

int main() {
  {
    // TEST: Constructor Default
    MEASUREMENT(LOOP(TEST::stack<std::string> stack;));
  }

  {
    // TEST: Operator=
    TEST::stack<std::string> stack;
    for (size_t i = 0; i < 10000; i++) {
      stack.push("hello");
    }
    MEASUREMENT(TEST::stack<std::string> stack_cp = stack);
  }

  {
    // TEST: empty() false
    TEST::stack<std::string> stack;
    stack.push("hello");
    MEASUREMENT(LOOP(stack.empty()))
  }

  {
    // TEST: empty() true
    TEST::stack<std::string> stack;
    MEASUREMENT(LOOP(stack.empty()))
  }

  {
    // TEST: size()
    TEST::stack<std::string> stack;
    for (size_t i = 0; i < 10000; i++) {
      stack.push("hello");
    }
    MEASUREMENT(LOOP(stack.size()))
  }

  {
    // TEST: top()
    TEST::stack<std::string> stack;
    for (size_t i = 0; i < 1001; i++) {
      stack.push("hello");
    }
    MEASUREMENT(LOOP(stack.top()))
  }

  {
    // TEST: top() const
    TEST::stack<std::string> stack;
    for (size_t i = 0; i < 1001; i++) {
      stack.push("hello");
    }
    const TEST::stack<std::string> cstack;
    MEASUREMENT(LOOP(stack.top()))
  }

  {
    // TEST: push()
    TEST::stack<std::string> stack;
    MEASUREMENT(LOOP(stack.push("hello")))
  }

  {
    // TEST: pop()
    TEST::stack<std::string> stack;
    for (size_t i = 0; i < 100001; i++) {
      stack.push("hello");
    }
    MEASUREMENT(LOOP(stack.pop()))
  }

  {
    TEST::stack<std::string> stack;
    for (size_t i = 0; i < 1001; i++) {
      stack.push("hello");
    }
    TEST::stack<std::string> stack2;
    for (size_t i = 0; i < 1001; i++) {
      stack2.push("hello");
    }

    // TEST: operator==
    MEASUREMENT(bool a = (stack == stack2); (void)(a))
    // TEST: operator!=
    MEASUREMENT(bool a = (stack != stack2); (void)(a))
    // TEST: operator>
    MEASUREMENT(bool a = (stack > stack2); (void)(a))
    // TEST: operator<
    MEASUREMENT(bool a = (stack < stack2); (void)(a))
    // TEST: operator>=
    MEASUREMENT(bool a = (stack >= stack2); (void)(a))
    // TEST: operator<=
    MEASUREMENT(bool a = (stack <= stack2); (void)(a))
  }
}