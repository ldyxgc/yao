#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>

#include "yao/def/check.hpp"
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

  { // ns = false, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::lab::prt::osprint_value(oss, val);
      return oss.str() == out;
    };

    YAO_CHECK(test(true, "bool: true"));
    YAO_CHECK(test(false, "bool: false"));

    YAO_CHECK(test(char{INT8_MIN}, "char: 0x80"));
    YAO_CHECK(test(char{INT8_MAX}, "char: 0x7F"));
    YAO_CHECK(test(char{'\x00'}, "char: 0x00"));
    YAO_CHECK(test(char{'\xFF'}, "char: 0xFF"));

    YAO_CHECK(test(std::int8_t{INT8_MIN}, "int8_t: -128"));
    YAO_CHECK(test(std::int8_t{INT8_MAX}, "int8_t: 127"));
    YAO_CHECK(test(std::uint8_t{0}, "uint8_t: 0"));
    YAO_CHECK(test(std::uint8_t{UINT8_MAX}, "uint8_t: 255"));

    YAO_CHECK(test(std::int16_t{INT16_MIN}, "int16_t: -32768"));
    YAO_CHECK(test(std::int16_t{INT16_MAX}, "int16_t: 32767"));
    YAO_CHECK(test(std::uint16_t{0}, "uint16_t: 0"));
    YAO_CHECK(test(std::uint16_t{UINT16_MAX}, "uint16_t: 65535"));

    YAO_CHECK(test(std::int32_t{INT32_MIN}, "int32_t: -2147483648"));
    YAO_CHECK(test(std::int32_t{INT32_MAX}, "int32_t: 2147483647"));
    YAO_CHECK(test(std::uint32_t{0}, "uint32_t: 0"));
    YAO_CHECK(test(std::uint32_t{UINT32_MAX}, "uint32_t: 4294967295"));

    YAO_CHECK(test(std::int64_t{INT64_MIN}, "int64_t: -9223372036854775808"));
    YAO_CHECK(test(std::int64_t{INT64_MAX}, "int64_t: 9223372036854775807"));
    YAO_CHECK(test(std::uint64_t{0}, "uint64_t: 0"));
    YAO_CHECK(
        test(std::uint64_t{UINT64_MAX}, "uint64_t: 18446744073709551615"));

    YAO_CHECK(test(Int8{INT8_MIN}, "Int8: {_i8:int8_t: -128}"));
    YAO_CHECK(test(Int8{INT8_MAX}, "Int8: {_i8:int8_t: 127}"));
    YAO_CHECK(test(Uint8{0}, "Uint8: {_u8:uint8_t: 0}"));
    YAO_CHECK(test(Uint8{UINT8_MAX}, "Uint8: {_u8:uint8_t: 255}"));

    YAO_CHECK(test(std::set<Int8>{9, 8, 7}, "set: {"
                                            "0:Int8: {_i8:int8_t: 7},"
                                            "1:Int8: {_i8:int8_t: 8},"
                                            "2:Int8: {_i8:int8_t: 9}"
                                            "}"));
    YAO_CHECK(test(std::map<Uint8, Int8>{{std::uint8_t{7}, std::int8_t{-1}},
                                         {std::uint8_t{9}, std::int8_t{-3}},
                                         {std::uint8_t{8}, std::int8_t{-2}}},
                   "map: {"
                   "0: {Uint8: {_u8:uint8_t: 7},Int8: {_i8:int8_t: -1}},"
                   "1: {Uint8: {_u8:uint8_t: 8},Int8: {_i8:int8_t: -2}},"
                   "2: {Uint8: {_u8:uint8_t: 9},Int8: {_i8:int8_t: -3}}"
                   "}"));

    YAO_CHECK(test(std::unique_ptr<Int8>{}, "unique_ptr: {}"));
    YAO_CHECK(
        test(std::make_unique<Int8>(), "unique_ptr: {Int8: {_i8:int8_t: 0}}"));
    YAO_CHECK(test(std::shared_ptr<Uint8>{}, "shared_ptr: {}"));
    YAO_CHECK(test(std::make_shared<Uint8>(),
                   "shared_ptr: {Uint8: {_u8:uint8_t: 0}}"));
  }

  { // ns = true, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::lab::prt::osprint_value<true>(oss, val);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool: false"));
    YAO_CHECK(test(char{}, "char: 0x00"));

    YAO_CHECK(test(std::int8_t{}, "std::int8_t: 0"));
    YAO_CHECK(test(std::uint8_t{}, "std::uint8_t: 0"));
    YAO_CHECK(test(std::int16_t{}, "std::int16_t: 0"));
    YAO_CHECK(test(std::uint16_t{}, "std::uint16_t: 0"));
    YAO_CHECK(test(std::int32_t{}, "std::int32_t: 0"));
    YAO_CHECK(test(std::uint32_t{}, "std::uint32_t: 0"));
    YAO_CHECK(test(std::int64_t{}, "std::int64_t: 0"));
    YAO_CHECK(test(std::uint64_t{}, "std::uint64_t: 0"));

    YAO_CHECK(test(Int8{}, "Int8: {_i8:std::int8_t: 0}"));
    YAO_CHECK(test(Uint8{}, "Uint8: {_u8:std::uint8_t: 0}"));

    YAO_CHECK(test(std::set<Int8>{9, 8, 7}, "std::set: {"
                                            "0:Int8: {_i8:std::int8_t: 7},"
                                            "1:Int8: {_i8:std::int8_t: 8},"
                                            "2:Int8: {_i8:std::int8_t: 9}"
                                            "}"));
    YAO_CHECK(
        test(std::map<Uint8, Int8>{{std::uint8_t{7}, std::int8_t{-1}},
                                   {std::uint8_t{9}, std::int8_t{-3}},
                                   {std::uint8_t{8}, std::int8_t{-2}}},
             "std::map: {"
             "0: {Uint8: {_u8:std::uint8_t: 7},Int8: {_i8:std::int8_t: -1}},"
             "1: {Uint8: {_u8:std::uint8_t: 8},Int8: {_i8:std::int8_t: -2}},"
             "2: {Uint8: {_u8:std::uint8_t: 9},Int8: {_i8:std::int8_t: -3}}"
             "}"));

    YAO_CHECK(test(std::unique_ptr<Int8>{}, "std::unique_ptr: {}"));
    YAO_CHECK(test(std::make_unique<Int8>(),
                   "std::unique_ptr: {Int8: {_i8:std::int8_t: 0}}"));
    YAO_CHECK(test(std::shared_ptr<Uint8>{}, "std::shared_ptr: {}"));
    YAO_CHECK(test(std::make_shared<Uint8>(),
                   "std::shared_ptr: {Uint8: {_u8:std::uint8_t: 0}}"));
  }

  { // ns = false, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::lab::prt::osprint_value<false, true>(oss, val);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool: false"));
    YAO_CHECK(test(char{}, "char: 0x00"));

    YAO_CHECK(test(std::int8_t{}, "int8_t: 0"));
    YAO_CHECK(test(std::uint8_t{}, "uint8_t: 0"));
    YAO_CHECK(test(std::int16_t{}, "int16_t: 0"));
    YAO_CHECK(test(std::uint16_t{}, "uint16_t: 0"));
    YAO_CHECK(test(std::int32_t{}, "int32_t: 0"));
    YAO_CHECK(test(std::uint32_t{}, "uint32_t: 0"));
    YAO_CHECK(test(std::int64_t{}, "int64_t: 0"));
    YAO_CHECK(test(std::uint64_t{}, "uint64_t: 0"));

    YAO_CHECK(test(Int8{}, "Int8: {_i8:int8_t: 0}"));
    YAO_CHECK(test(Uint8{}, "Uint8: {_u8:uint8_t: 0}"));

    YAO_CHECK(test(std::set<Int8>{9, 8, 7}, "set<Int8>: {"
                                            "0:Int8: {_i8:int8_t: 7},"
                                            "1:Int8: {_i8:int8_t: 8},"
                                            "2:Int8: {_i8:int8_t: 9}"
                                            "}"));
    YAO_CHECK(test(std::map<Uint8, Int8>{{std::uint8_t{7}, std::int8_t{-1}},
                                         {std::uint8_t{9}, std::int8_t{-3}},
                                         {std::uint8_t{8}, std::int8_t{-2}}},
                   "map<Uint8|Int8>: {"
                   "0: {Uint8: {_u8:uint8_t: 7},Int8: {_i8:int8_t: -1}},"
                   "1: {Uint8: {_u8:uint8_t: 8},Int8: {_i8:int8_t: -2}},"
                   "2: {Uint8: {_u8:uint8_t: 9},Int8: {_i8:int8_t: -3}}"
                   "}"));

    YAO_CHECK(test(std::unique_ptr<Int8>{}, "unique_ptr<Int8>: {}"));
    YAO_CHECK(test(std::make_unique<Int8>(),
                   "unique_ptr<Int8>: {Int8: {_i8:int8_t: 0}}"));
    YAO_CHECK(test(std::shared_ptr<Uint8>{}, "shared_ptr<Uint8>: {}"));
    YAO_CHECK(test(std::make_shared<Uint8>(),
                   "shared_ptr<Uint8>: {Uint8: {_u8:uint8_t: 0}}"));
  }

  { // ns = true, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::lab::prt::osprint_value<true, true>(oss, val);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool: false"));
    YAO_CHECK(test(char{}, "char: 0x00"));

    YAO_CHECK(test(std::int8_t{}, "std::int8_t: 0"));
    YAO_CHECK(test(std::uint8_t{}, "std::uint8_t: 0"));
    YAO_CHECK(test(std::int16_t{}, "std::int16_t: 0"));
    YAO_CHECK(test(std::uint16_t{}, "std::uint16_t: 0"));
    YAO_CHECK(test(std::int32_t{}, "std::int32_t: 0"));
    YAO_CHECK(test(std::uint32_t{}, "std::uint32_t: 0"));
    YAO_CHECK(test(std::int64_t{}, "std::int64_t: 0"));
    YAO_CHECK(test(std::uint64_t{}, "std::uint64_t: 0"));

    YAO_CHECK(test(Int8{}, "Int8: {_i8:std::int8_t: 0}"));
    YAO_CHECK(test(Uint8{}, "Uint8: {_u8:std::uint8_t: 0}"));

    YAO_CHECK(test(std::set<Int8>{9, 8, 7}, "std::set<Int8>: {"
                                            "0:Int8: {_i8:std::int8_t: 7},"
                                            "1:Int8: {_i8:std::int8_t: 8},"
                                            "2:Int8: {_i8:std::int8_t: 9}"
                                            "}"));
    YAO_CHECK(
        test(std::map<Uint8, Int8>{{std::uint8_t{7}, std::int8_t{-1}},
                                   {std::uint8_t{9}, std::int8_t{-3}},
                                   {std::uint8_t{8}, std::int8_t{-2}}},
             "std::map<Uint8|Int8>: {"
             "0: {Uint8: {_u8:std::uint8_t: 7},Int8: {_i8:std::int8_t: -1}},"
             "1: {Uint8: {_u8:std::uint8_t: 8},Int8: {_i8:std::int8_t: -2}},"
             "2: {Uint8: {_u8:std::uint8_t: 9},Int8: {_i8:std::int8_t: -3}}"
             "}"));

    YAO_CHECK(test(std::unique_ptr<Int8>{}, "std::unique_ptr<Int8>: {}"));
    YAO_CHECK(test(std::make_unique<Int8>(),
                   "std::unique_ptr<Int8>: {Int8: {_i8:std::int8_t: 0}}"));
    YAO_CHECK(test(std::shared_ptr<Uint8>{}, "std::shared_ptr<Uint8>: {}"));
    YAO_CHECK(test(std::make_shared<Uint8>(),
                   "std::shared_ptr<Uint8>: {Uint8: {_u8:std::uint8_t: 0}}"));
  }

  return 0;
}
