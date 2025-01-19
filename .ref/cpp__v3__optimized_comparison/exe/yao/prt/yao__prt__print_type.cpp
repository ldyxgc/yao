#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/com/integral.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/print_type.hpp"

using namespace yao::com;
using yao::prt::PrintTypeArgs;

namespace box {

template <typename T> struct Box {
  static void print_type(std::ostream &os, const PrintTypeArgs &args = {});
};

template <typename T>
void Box<T>::print_type(std::ostream &os, const PrintTypeArgs &args) {
  if (args.scope)
    os << "box::";
  os << "Box";
  if (args.tmpl_args) {
    os << '<';
    yao::prt::print_type<T>(os, args);
    os << '>';
  }
}

} // namespace box

template <typename T>
void demo(const PrintTypeArgs &args = {.scope = true, .tmpl_args = true}) {
  yao::prt::print_type<T>(std::cout, args);
  std::cout << '\n';
}

int main() {

  demo<bool>();
  demo<char>();
  std::cout << '\n';

  demo<schar>();
  demo<uchar>();
  demo<short>();
  demo<ushort>();
  demo<int>();
  demo<uint>();
  demo<long>();
  demo<ulong>();
  demo<llong>();
  demo<ullong>();
  std::cout << '\n';

  demo<box::Box<int>>();
  demo<box::Box<box::Box<int>>>();
  std::cout << '\n';

  demo<std::set<box::Box<char>>>();
  demo<std::map<box::Box<char>, box::Box<bool>>>();
  std::cout << '\n';

  demo<std::unique_ptr<box::Box<bool>>>();
  demo<std::shared_ptr<box::Box<char>>>();

  return 0;
}
