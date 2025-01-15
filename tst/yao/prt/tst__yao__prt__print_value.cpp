#include <sstream>

#include "yao/com/integral.hpp"
#include "yao/def/check.hpp"
#include "yao/prt/print_value.hpp"

using namespace yao::com;

int main() {

  auto test = [](auto val, auto out) {
    std::ostringstream oss;
    yao::prt::print_value(oss, val);
    return oss.str() == out;
  };

  YAO_CHECK(test(true, "bool: true"));
  YAO_CHECK(test(false, "bool: false"));
  YAO_CHECK(test(char{'\x00'}, "char: 0x00"));
  YAO_CHECK(test(char{'\xFF'}, "char: 0xFF"));

  YAO_CHECK(test(schar{0}, "schar: 0"));
  YAO_CHECK(test(uchar{1}, "uchar: 1"));
  YAO_CHECK(test(short{2}, "short: 2"));
  YAO_CHECK(test(ushort{3}, "ushort: 3"));
  YAO_CHECK(test(int{4}, "int: 4"));
  YAO_CHECK(test(uint{5}, "uint: 5"));
  YAO_CHECK(test(long{6}, "long: 6"));
  YAO_CHECK(test(ulong{7}, "ulong: 7"));
  YAO_CHECK(test(llong{8}, "llong: 8"));
  YAO_CHECK(test(ullong{9}, "ullong: 9"));

  return 0;
}
