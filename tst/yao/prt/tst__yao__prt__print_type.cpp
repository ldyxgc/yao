#include <sstream>

#include "yao/com/integral.hpp"
#include "yao/def/check.hpp"
#include "yao/prt/print_type.hpp"

using namespace yao::com;

int main() {

  auto test = []<typename T>(auto out) {
    std::ostringstream oss;
    yao::prt::print_type<T>(oss);
    return oss.str() == out;
  };

  YAO_CHECK(test.operator()<bool>("bool"));
  YAO_CHECK(test.operator()<char>("char"));

  YAO_CHECK(test.operator()<schar>("schar"));
  YAO_CHECK(test.operator()<uchar>("uchar"));
  YAO_CHECK(test.operator()<short>("short"));
  YAO_CHECK(test.operator()<ushort>("ushort"));
  YAO_CHECK(test.operator()<int>("int"));
  YAO_CHECK(test.operator()<uint>("uint"));
  YAO_CHECK(test.operator()<long>("long"));
  YAO_CHECK(test.operator()<ulong>("ulong"));
  YAO_CHECK(test.operator()<llong>("llong"));
  YAO_CHECK(test.operator()<ullong>("ullong"));

  return 0;
}
