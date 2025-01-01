#include <cstdint>
#include <iostream>

#include "yao/prt/print_type.hpp"

int main() {

  auto demo = []<typename T>() {
    yao::prt::print_type<T, true, true>(std::cout);
    std::cout << '\n';
  };

  demo.operator()<bool>();
  demo.operator()<char>();
  std::cout << '\n';

  demo.operator()<std::int8_t>();
  demo.operator()<std::uint8_t>();
  demo.operator()<std::int16_t>();
  demo.operator()<std::uint16_t>();
  demo.operator()<std::int32_t>();
  demo.operator()<std::uint32_t>();
  demo.operator()<std::int64_t>();
  demo.operator()<std::uint64_t>();

  return 0;
}
