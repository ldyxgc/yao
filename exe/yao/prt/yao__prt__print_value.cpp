#include <cstdint>
#include <iostream>
#include <map>
#include <ostream>
#include <set>

#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace box {

template <typename T> struct Box {
  T _t;
  Box(const T &t = {});
  template <bool ns, bool tp> static void print_type(std::ostream &os);
  template <bool ns, bool tp> void print_value(std::ostream &os) const;
};

template <typename T> Box<T>::Box(const T &t) : _t{t} {}

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

template <typename T>
template <bool ns, bool tp>
void Box<T>::print_value(std::ostream &os) const {
  print_type<ns, tp>(os);
  os << ": {_t:";
  yao::prt::print_value<ns, tp>(os, _t);
  os << '}';
}

} // namespace box

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
  std::cout << '\n';

  demo(box::Box<std::int8_t>{});
  demo(box::Box<box::Box<std::int8_t>>{});
  std::cout << '\n';

  demo(std::set<std::int8_t>{-1, -2, -3});
  demo(std::map<std::int8_t, std::uint8_t>{{-1, 1}, {-2, 2}, {-3, 3}});

  return 0;
}
