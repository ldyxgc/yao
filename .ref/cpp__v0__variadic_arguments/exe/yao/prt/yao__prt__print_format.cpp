#include <iostream>

#include "yao/prt/print_format.hpp"

int main() {

  auto demo = [](auto fmt, auto... args) {
    yao::prt::print_format(std::cout, fmt, args...);
    std::cout << '\n';
  };

  demo("0x%02x", 0xF);
  demo("0x%02X", 0xf);
  std::cout << '\n';

  demo("0");
  demo("0 %c", '1');
  demo("0 %c %s", '1', "2");
  demo("0 %c %s %i", '1', "2", 3);
  demo("0 %c %s %i %.0f", '1', "2", 3, 4.0);

  return 0;
}
