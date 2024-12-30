#include <sstream>

#include "yao/def/check.hpp"
#include "yao/prt/impl/tmpl/print_format.hpp"

int main() {

  auto test = [](auto out, auto fmt, auto... args) {
    std::ostringstream oss;
    yao::prt::impl::tmpl::print_format(oss, fmt, args...);
    return oss.str() == out;
  };

  YAO_CHECK(test("0x0f", "0x%02x", 0xF));
  YAO_CHECK(test("0x0F", "0x%02X", 0xf));

  YAO_CHECK(test("0", "0"));
  YAO_CHECK(test("0 1", "0 %c", '1'));
  YAO_CHECK(test("0 1 2", "0 %c %s", '1', "2"));
  YAO_CHECK(test("0 1 2 3", "0 %c %s %i", '1', "2", 3));
  YAO_CHECK(test("0 1 2 3 4", "0 %c %s %i %.0f", '1', "2", 3, 4.0));

  return 0;
}
