#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>

#include "yao/def/check.hpp"
#include "yao/prt/osprint_type.hpp"

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
    yao::prt::osprint_type<T, ns, tp>(os);
    os << '>';
  }
}

} // namespace box

int main() {

  { // ns = false, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::osprint_type<decltype(val)>(oss);
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

    YAO_CHECK(test(box::Box<bool>{}, "Box"));

    YAO_CHECK(test(std::set<box::Box<char>>{}, "set"));
    YAO_CHECK(test(std::map<box::Box<bool>, box::Box<char>>{}, "map"));

    YAO_CHECK(test(std::unique_ptr<box::Box<bool>>{}, "unique_ptr"));
    YAO_CHECK(test(std::shared_ptr<box::Box<char>>{}, "shared_ptr"));
  }

  { // ns = true, tp = false
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::osprint_type<decltype(val), true>(oss);
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

    YAO_CHECK(test(box::Box<bool>{}, "box::Box"));

    YAO_CHECK(test(std::set<box::Box<char>>{}, "std::set"));
    YAO_CHECK(test(std::map<box::Box<bool>, box::Box<char>>{}, "std::map"));

    YAO_CHECK(test(std::unique_ptr<box::Box<bool>>{}, "std::unique_ptr"));
    YAO_CHECK(test(std::shared_ptr<box::Box<char>>{}, "std::shared_ptr"));
  }

  { // ns = false, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::osprint_type<decltype(val), false, true>(oss);
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

    YAO_CHECK(test(box::Box<bool>{}, "Box<bool>"));

    YAO_CHECK(test(std::set<box::Box<char>>{}, "set<Box<char>>"));
    YAO_CHECK(test(std::map<box::Box<bool>, box::Box<char>>{},
                   "map<Box<bool>|Box<char>>"));

    YAO_CHECK(test(std::unique_ptr<box::Box<bool>>{}, "unique_ptr<Box<bool>>"));
    YAO_CHECK(test(std::shared_ptr<box::Box<char>>{}, "shared_ptr<Box<char>>"));
  }

  { // ns = true, tp = true
    auto test = [](auto val, auto out) {
      std::ostringstream oss;
      yao::prt::osprint_type<decltype(val), true, true>(oss);
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

    YAO_CHECK(test(box::Box<bool>{}, "box::Box<bool>"));

    YAO_CHECK(test(std::set<box::Box<char>>{}, "std::set<box::Box<char>>"));
    YAO_CHECK(test(std::map<box::Box<bool>, box::Box<char>>{},
                   "std::map<box::Box<bool>|box::Box<char>>"));

    YAO_CHECK(test(std::unique_ptr<box::Box<bool>>{},
                   "std::unique_ptr<box::Box<bool>>"));
    YAO_CHECK(test(std::shared_ptr<box::Box<char>>{},
                   "std::shared_ptr<box::Box<char>>"));
  }

  return 0;
}
