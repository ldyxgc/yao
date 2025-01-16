#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>

#include "yao/com/integral.hpp"
#include "yao/def/check.hpp"
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
  static void print_type(std::ostream &os, const PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const PrintValueArgs &args = {},
                   uint indent_level = 0) const;
};

template <typename T> Box<T>::Box(const T &t) : _t{t} {}

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

bool test(auto val, const PrintValueArgs &args, auto out) {
  std::ostringstream oss;
  yao::prt::print_value(oss, val, args);
  return oss.str() == out;
}

bool test(auto val, auto out) {
  return test(std::forward<decltype(val)>(val), {}, out);
}

int main() {

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

  YAO_CHECK(test(box::Box<int>{}, "Box:\n"
                                  "  _t:int: 0"));
  YAO_CHECK(test(box::Box<int>{}, {.print_type_args = {.scope = true}},
                 "box::Box:\n"
                 "  _t:int: 0"));
  YAO_CHECK(test(box::Box<int>{}, {.print_type_args = {.tmpl_args = true}},
                 "Box<int>:\n"
                 "  _t:int: 0"));

  YAO_CHECK(test(box::Box<box::Box<int>>{}, "Box:\n"
                                            "  _t:Box:\n"
                                            "    _t:int: 0"));
  YAO_CHECK(test(box::Box<box::Box<int>>{},
                 {.print_type_args = {.scope = true}},
                 "box::Box:\n"
                 "  _t:box::Box:\n"
                 "    _t:int: 0"));
  YAO_CHECK(test(box::Box<box::Box<int>>{},
                 {.print_type_args = {.tmpl_args = true}},
                 "Box<Box<int>>:\n"
                 "  _t:Box<int>:\n"
                 "    _t:int: 0"));

  YAO_CHECK(test(std::set<int>{-1, -2, -3}, "set:\n"
                                            "  - int: -3\n"
                                            "  - int: -2\n"
                                            "  - int: -1"));
  YAO_CHECK(test(std::set<int>{-1, -2, -3},
                 {.print_type_args = {.scope = true}},
                 "std::set:\n"
                 "  - int: -3\n"
                 "  - int: -2\n"
                 "  - int: -1"));
  YAO_CHECK(test(std::set<int>{-1, -2, -3},
                 {.print_type_args = {.tmpl_args = true}},
                 "set<int>:\n"
                 "  - int: -3\n"
                 "  - int: -2\n"
                 "  - int: -1"));

  YAO_CHECK(test(std::map<int, uint>{{-1, 1u}, {-2, 2u}, {-3, 3u}},
                 "map:\n"
                 "  - int: -3\n"
                 "    uint: 3\n"
                 "  - int: -2\n"
                 "    uint: 2\n"
                 "  - int: -1\n"
                 "    uint: 1"));
  YAO_CHECK(test(std::map<int, uint>{{-1, 1u}, {-2, 2u}, {-3, 3u}},
                 {.print_type_args = {.scope = true}},
                 "std::map:\n"
                 "  - int: -3\n"
                 "    uint: 3\n"
                 "  - int: -2\n"
                 "    uint: 2\n"
                 "  - int: -1\n"
                 "    uint: 1"));
  YAO_CHECK(test(std::map<int, uint>{{-1, 1u}, {-2, 2u}, {-3, 3u}},
                 {.print_type_args = {.tmpl_args = true}},
                 "map<int,uint>:\n"
                 "  - int: -3\n"
                 "    uint: 3\n"
                 "  - int: -2\n"
                 "    uint: 2\n"
                 "  - int: -1\n"
                 "    uint: 1"));

  YAO_CHECK(test(std::unique_ptr<box::Box<int>>{}, "unique_ptr:"));
  YAO_CHECK(test(std::unique_ptr<box::Box<int>>{},
                 {.print_type_args = {.scope = true}}, "std::unique_ptr:"));
  YAO_CHECK(test(std::unique_ptr<box::Box<int>>{},
                 {.print_type_args = {.tmpl_args = true}},
                 "unique_ptr<Box<int>>:"));

  YAO_CHECK(test(std::make_unique<box::Box<int>>(), "unique_ptr:\n"
                                                    "  Box:\n"
                                                    "    _t:int: 0"));
  YAO_CHECK(test(std::make_unique<box::Box<int>>(),
                 {.print_type_args = {.scope = true}},
                 "std::unique_ptr:\n"
                 "  box::Box:\n"
                 "    _t:int: 0"));
  YAO_CHECK(test(std::make_unique<box::Box<int>>(),
                 {.print_type_args = {.tmpl_args = true}},
                 "unique_ptr<Box<int>>:\n"
                 "  Box<int>:\n"
                 "    _t:int: 0"));

  YAO_CHECK(test(std::shared_ptr<box::Box<uint>>{}, "shared_ptr:"));
  YAO_CHECK(test(std::shared_ptr<box::Box<uint>>{},
                 {.print_type_args = {.scope = true}}, "std::shared_ptr:"));
  YAO_CHECK(test(std::shared_ptr<box::Box<uint>>{},
                 {.print_type_args = {.tmpl_args = true}},
                 "shared_ptr<Box<uint>>:"));

  YAO_CHECK(test(std::make_shared<box::Box<uint>>(), "shared_ptr:\n"
                                                     "  Box:\n"
                                                     "    _t:uint: 0"));
  YAO_CHECK(test(std::make_shared<box::Box<uint>>(),
                 {.print_type_args = {.scope = true}},
                 "std::shared_ptr:\n"
                 "  box::Box:\n"
                 "    _t:uint: 0"));
  YAO_CHECK(test(std::make_shared<box::Box<uint>>(),
                 {.print_type_args = {.tmpl_args = true}},
                 "shared_ptr<Box<uint>>:\n"
                 "  Box<uint>:\n"
                 "    _t:uint: 0"));

  return 0;
}
