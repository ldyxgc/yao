#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/com/integral.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

using namespace yao::com;
using yao::prt::PrintTypeArgs;
using yao::prt::PrintValueArgs;

namespace box {

template <typename T> struct Box {
  T _t;
  Box(const T &t = {});
  operator T() const;
  static void print_type(std::ostream &os, const PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const PrintValueArgs &args = {},
                   uint indent_level = 0) const;
};

template <typename T> Box<T>::Box(const T &t) : _t{t} {}

template <typename T> Box<T>::operator T() const { return _t; }

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

template <typename T>
void Box<T>::print_value(std::ostream &os, const PrintValueArgs &args,
                         uint indent_level) const {
  print_type(os, args.print_type_args);
  os << ":\n";
  ++indent_level;
  yao::prt::print_indent(os, indent_level);
  os << "_t:";
  yao::prt::print_value(os, _t, args, indent_level);
}

} // namespace box

void demo(auto val,
          const PrintValueArgs &args = {
              .print_type_args = {.scope = true, .tmpl_args = true}}) {
  yao::prt::print_value(std::cout, val, args);
  std::cout << '\n';
}

int main() {

  demo(true);
  demo(false);
  demo(char{'\x00'});
  demo(char{'\xFF'});
  std::cout << '\n';

  demo(schar{0});
  demo(uchar{1});
  demo(short{2});
  demo(ushort{3});
  demo(int{4});
  demo(uint{5});
  demo(long{6});
  demo(ulong{7});
  demo(llong{8});
  demo(ullong{9});
  std::cout << '\n';

  demo(box::Box<int>{});
  demo(box::Box<box::Box<int>>{});
  std::cout << '\n';

  demo(std::set<box::Box<int>>{-1, -2, -3});
  demo(std::map<box::Box<int>, box::Box<uint>>{{-1, 1u}, {-2, 2u}, {-3, 3u}});
  std::cout << '\n';

  demo(std::unique_ptr<box::Box<int>>{});
  demo(std::make_unique<box::Box<int>>());
  demo(std::shared_ptr<box::Box<uint>>{});
  demo(std::make_shared<box::Box<uint>>());

  return 0;
}
