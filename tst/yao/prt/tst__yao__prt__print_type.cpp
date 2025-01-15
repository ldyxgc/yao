#include <map>
#include <ostream>
#include <set>
#include <sstream>

#include "yao/com/integral.hpp"
#include "yao/def/check.hpp"
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

template <typename T> bool test(const PrintTypeArgs &args, auto out) {
  std::ostringstream oss;
  yao::prt::print_type<T>(oss, args);
  return oss.str() == out;
}

template <typename T> bool test(auto out) { return test<T>({}, out); }

int main() {

  YAO_CHECK(test<bool>("bool"));
  YAO_CHECK(test<char>("char"));

  YAO_CHECK(test<schar>("schar"));
  YAO_CHECK(test<uchar>("uchar"));
  YAO_CHECK(test<short>("short"));
  YAO_CHECK(test<ushort>("ushort"));
  YAO_CHECK(test<int>("int"));
  YAO_CHECK(test<uint>("uint"));
  YAO_CHECK(test<long>("long"));
  YAO_CHECK(test<ulong>("ulong"));
  YAO_CHECK(test<llong>("llong"));
  YAO_CHECK(test<ullong>("ullong"));

  YAO_CHECK(test<box::Box<int>>("Box"));
  YAO_CHECK(test<box::Box<int>>({.scope = true}, "box::Box"));
  YAO_CHECK(test<box::Box<int>>({.tmpl_args = true}, "Box<int>"));

  YAO_CHECK(test<box::Box<box::Box<int>>>("Box"));
  YAO_CHECK(test<box::Box<box::Box<int>>>({.scope = true}, "box::Box"));
  YAO_CHECK(
      test<box::Box<box::Box<int>>>({.tmpl_args = true}, "Box<Box<int>>"));

  YAO_CHECK(test<std::set<box::Box<char>>>("set"));
  YAO_CHECK(test<std::set<box::Box<char>>>({.scope = true}, "std::set"));
  YAO_CHECK(
      test<std::set<box::Box<char>>>({.tmpl_args = true}, "set<Box<char>>"));

  YAO_CHECK(test<std::map<box::Box<char>, box::Box<bool>>>("map"));
  YAO_CHECK(test<std::map<box::Box<char>, box::Box<bool>>>({.scope = true},
                                                           "std::map"));
  YAO_CHECK(test<std::map<box::Box<char>, box::Box<bool>>>(
      {.tmpl_args = true}, "map<Box<char>,Box<bool>>"));

  return 0;
}
