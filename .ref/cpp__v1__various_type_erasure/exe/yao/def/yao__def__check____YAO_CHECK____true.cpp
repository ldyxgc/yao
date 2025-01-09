#include <iostream>

#include "yao/def/check.hpp"

int main() {

  std::cout << "Ahead: YAO_CHECK(true);\n";
  YAO_CHECK(true);
  std::cout << "After: YAO_CHECK(true);\n";

  return 0;
}
