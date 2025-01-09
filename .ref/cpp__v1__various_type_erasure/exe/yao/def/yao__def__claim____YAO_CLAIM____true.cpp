#include <iostream>

#include "yao/config.hpp"
#include "yao/def/claim.hpp"

int main() {

  std::cout << "Build: ";
#if YAO_CONFIG__BUILD_TYPE == YAO_CONFIG__BUILD_TYPE__DEBUG
  std::cout << "Debug\n";
#elif YAO_CONFIG__BUILD_TYPE == YAO_CONFIG__BUILD_TYPE__RELEASE
  std::cout << "Release\n";
#endif

  std::cout << "Ahead: YAO_CLAIM(true);\n";
  YAO_CLAIM(true);
  std::cout << "After: YAO_CLAIM(true);\n";

  return 0;
}
