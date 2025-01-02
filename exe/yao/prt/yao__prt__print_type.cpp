#include <cstdint>
#include <iostream>
#include <ostream>

#include "yao/prt/print_type.hpp"

namespace box {

template <typename T> struct Box {
  template <bool ns, bool tp> static void print_type(std::ostream &os);
};

template <typename T>
template <bool ns, bool tp>
void Box<T>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "box::";
  os << "Box";
  if constexpr (tp) {
    os << '<';
    yao::prt::print_type<T, ns, tp>(os);
    os << '>';
  }
}

} // namespace box

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
  std::cout << '\n';

  demo.operator()<box::Box<std::int8_t>>();
  demo.operator()<box::Box<box::Box<std::int8_t>>>();

  return 0;
}
