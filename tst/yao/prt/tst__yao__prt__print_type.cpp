#include <cstdint>
#include <sstream>

#include "yao/def/check.hpp"
#include "yao/prt/print_type.hpp"

int main() {

  { // ns = false, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_type<decltype(val)>(oss);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool"));
    YAO_CHECK(test(char{}, "char"));

    YAO_CHECK(test(std::int8_t{}, "int8_t"));
    YAO_CHECK(test(std::uint8_t{}, "uint8_t"));
    YAO_CHECK(test(std::int16_t{}, "int16_t"));
    YAO_CHECK(test(std::uint16_t{}, "uint16_t"));
    YAO_CHECK(test(std::int32_t{}, "int32_t"));
    YAO_CHECK(test(std::uint32_t{}, "uint32_t"));
    YAO_CHECK(test(std::int64_t{}, "int64_t"));
    YAO_CHECK(test(std::uint64_t{}, "uint64_t"));
  }

  { // ns = true, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_type<decltype(val), true>(oss);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool"));
    YAO_CHECK(test(char{}, "char"));

    YAO_CHECK(test(std::int8_t{}, "std::int8_t"));
    YAO_CHECK(test(std::uint8_t{}, "std::uint8_t"));
    YAO_CHECK(test(std::int16_t{}, "std::int16_t"));
    YAO_CHECK(test(std::uint16_t{}, "std::uint16_t"));
    YAO_CHECK(test(std::int32_t{}, "std::int32_t"));
    YAO_CHECK(test(std::uint32_t{}, "std::uint32_t"));
    YAO_CHECK(test(std::int64_t{}, "std::int64_t"));
    YAO_CHECK(test(std::uint64_t{}, "std::uint64_t"));
  }

  { // ns = false, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_type<decltype(val), false, true>(oss);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool"));
    YAO_CHECK(test(char{}, "char"));

    YAO_CHECK(test(std::int8_t{}, "int8_t"));
    YAO_CHECK(test(std::uint8_t{}, "uint8_t"));
    YAO_CHECK(test(std::int16_t{}, "int16_t"));
    YAO_CHECK(test(std::uint16_t{}, "uint16_t"));
    YAO_CHECK(test(std::int32_t{}, "int32_t"));
    YAO_CHECK(test(std::uint32_t{}, "uint32_t"));
    YAO_CHECK(test(std::int64_t{}, "int64_t"));
    YAO_CHECK(test(std::uint64_t{}, "uint64_t"));
  }

  { // ns = true, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::print_type<decltype(val), true, true>(oss);
      return oss.str() == out;
    };

    YAO_CHECK(test(bool{}, "bool"));
    YAO_CHECK(test(char{}, "char"));

    YAO_CHECK(test(std::int8_t{}, "std::int8_t"));
    YAO_CHECK(test(std::uint8_t{}, "std::uint8_t"));
    YAO_CHECK(test(std::int16_t{}, "std::int16_t"));
    YAO_CHECK(test(std::uint16_t{}, "std::uint16_t"));
    YAO_CHECK(test(std::int32_t{}, "std::int32_t"));
    YAO_CHECK(test(std::uint32_t{}, "std::uint32_t"));
    YAO_CHECK(test(std::int64_t{}, "std::int64_t"));
    YAO_CHECK(test(std::uint64_t{}, "std::uint64_t"));
  }

  return 0;
}
