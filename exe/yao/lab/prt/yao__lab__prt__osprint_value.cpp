#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/lab/prt/osprint_type.hpp"
#include "yao/lab/prt/osprint_value.hpp"

struct Int8 {
  std::int8_t _i8;
  Int8(std::int8_t i8 = {}) : _i8{i8} {}
  operator std::int8_t() const { return _i8; }
  template <bool ns, bool tp> static void osprint_type(std::ostream &os) {
    os << "Int8";
  }
  template <bool ns, bool tp> void osprint_value(std::ostream &os) const {
    yao::lab::prt::osprint_type<Int8, ns, tp>(os);
    os << ": {_i8:";
    yao::lab::prt::osprint_value<ns, tp>(os, _i8);
    os << '}';
  }
};

struct Uint8 {
  std::uint8_t _u8;
  Uint8(std::uint8_t u8 = {}) : _u8{u8} {}
  operator std::uint8_t() const { return _u8; }
  template <bool ns, bool tp> static void osprint_type(std::ostream &os) {
    os << "Uint8";
  }
  void osprint_value(std::ostream &os, bool ns, bool tp) const {
    ns ? (tp ? yao::lab::prt::osprint_type<Uint8, true, true>(os)
             : yao::lab::prt::osprint_type<Uint8, true>(os))
       : (tp ? yao::lab::prt::osprint_type<Uint8, false, true>(os)
             : yao::lab::prt::osprint_type<Uint8>(os));
    os << ": {_u8:";
    ns ? (tp ? yao::lab::prt::osprint_value<true, true>(os, _u8)
             : yao::lab::prt::osprint_value<true>(os, _u8))
       : (tp ? yao::lab::prt::osprint_value<false, true>(os, _u8)
             : yao::lab::prt::osprint_value<>(os, _u8));
    os << '}';
  }
};

int main() {

  auto demo = [](auto val) {
    yao::lab::prt::osprint_value<true, true>(std::cout, val);
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

  demo(Int8{INT8_MIN});
  demo(Int8{INT8_MAX});
  demo(Uint8{0});
  demo(Uint8{UINT8_MAX});
  std::cout << '\n';

  demo(std::set<Int8>{7, 9, 8});
  demo(std::map<Uint8, Int8>{{std::uint8_t{7}, std::int8_t{-1}},
                             {std::uint8_t{9}, std::int8_t{-3}},
                             {std::uint8_t{8}, std::int8_t{-2}}});
  std::cout << '\n';

  demo(std::unique_ptr<Int8>{});
  demo(std::make_unique<Int8>());
  demo(std::shared_ptr<Uint8>{});
  demo(std::make_shared<Uint8>());

  return 0;
}
