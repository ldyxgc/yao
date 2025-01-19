#include <iostream>

#include "yao/def/check.hpp"

int main() {

  std::cout << "Ahead: YAO_CHECK(false);\n";
  YAO_CHECK(false);
  std::cout << "After: YAO_CHECK(false);\n";

  return 0;
}
