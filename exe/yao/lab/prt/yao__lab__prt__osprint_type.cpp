#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/lab/prt/osprint_type.hpp"

namespace box {

template <typename T> struct Box {
  template <bool ns, bool tp> static void osprint_type(std::ostream &os);
};

template <typename T>
template <bool ns, bool tp>
void Box<T>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "box::";
  os << "Box";
  if constexpr (tp) {
    os << '<';
    yao::lab::prt::osprint_type<T, ns, tp>(os);
    os << '>';
  }
}

} // namespace box

int main() {

  auto demo = []<typename T>() {
    yao::lab::prt::osprint_type<T, true, true>(std::cout);
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

  demo.operator()<box::Box<bool>>();
  std::cout << '\n';

  demo.operator()<std::set<box::Box<char>>>();
  demo.operator()<std::map<box::Box<bool>, box::Box<char>>>();
  std::cout << '\n';

  demo.operator()<std::unique_ptr<box::Box<bool>>>();
  demo.operator()<std::shared_ptr<box::Box<char>>>();

  return 0;
}
