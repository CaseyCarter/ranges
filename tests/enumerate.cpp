
#include "tl/enumerate.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>
template<class> struct TC;
TEST_CASE("basic vector") {
  std::vector a{1, 2, 3};
  int i = 0;
  for (auto&& [index, item] : a | tl::views::enumerate) {
    REQUIRE(index == i);
    REQUIRE(item == i + 1);
    ++i;
  }
}

TEST_CASE("basic const vector") {
  const std::vector a{1, 2, 3};
  int i = 0;
  for (auto&& [index, item] : a | tl::views::enumerate) {
    REQUIRE(index == i);
    REQUIRE(item == i + 1);
    ++i;
  }
}

TEST_CASE("transform") {
  const std::vector a{1, 2, 3};
  int i = 0;
  for (auto&& [index, item] :
       (a | std::views::transform([](auto i) { return i - 1; }) |
        tl::views::enumerate)) {
    REQUIRE(index == i);
    REQUIRE(item == i);
    ++i;
  }
}

TEST_CASE("modify vector") {
  std::vector a{1, 2, 3};
  int i = 0;
  for (auto&& [index, item] : a | tl::views::enumerate) {
    REQUIRE(index == i);
    REQUIRE(item == i + 1);
    item--;
    ++i;
  }
  i = 0;
  for (auto&& [index, item] : a | tl::views::enumerate) {
    REQUIRE(index == i);
    REQUIRE(item == i);
    ++i;
  }
  REQUIRE(a == std::vector{0, 1, 2});
}

TEST_CASE("issue #2") {
   for (auto&& [i, j] : (std::views::iota(0) | tl::views::enumerate | std::views::take(10))) {
      REQUIRE(i == j);
   }
}
