#include <cstdint>
#include <sstream>

#include "yao/def/check.hpp"
#include "yao/prt/print_value.hpp"

int main() {

  { // ns = false, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_value(oss, val);
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
  }

  { // ns = true, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_value<true>(oss, val);
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
  }

  { // ns = false, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_value<false, true>(oss, val);
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
  }

  { // ns = true, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_value<true, true>(oss, val);
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
  }

  return 0;
}
