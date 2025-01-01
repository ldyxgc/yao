#include <cstdint>
#include <iostream>

#include "yao/prt/print_value.hpp"

int main() {

  auto demo = [](auto val) {
    yao::prt::print_value<true, true>(std::cout, val);
    std::cout << '\n';
  };

  demo(true);
  demo(false);
  std::cout << '\n';

  demo(char{INT8_MIN});
  demo(char{INT8_MAX});
  demo(char{'\x00'});
  demo(char{'\xFF'});
  std::cout << '\n';

  demo(std::int8_t{INT8_MIN});
  demo(std::int8_t{INT8_MAX});
  demo(std::uint8_t{0});
  demo(std::uint8_t{UINT8_MAX});
  std::cout << '\n';

  demo(std::int16_t{INT16_MIN});
  demo(std::int16_t{INT16_MAX});
  demo(std::uint16_t{0});
  demo(std::uint16_t{UINT16_MAX});
  std::cout << '\n';

  demo(std::int32_t{INT32_MIN});
  demo(std::int32_t{INT32_MAX});
  demo(std::uint32_t{0});
  demo(std::uint32_t{UINT32_MAX});
  std::cout << '\n';

  demo(std::int64_t{INT64_MIN});
  demo(std::int64_t{INT64_MAX});
  demo(std::uint64_t{0});
  demo(std::uint64_t{UINT64_MAX});

  return 0;
}
