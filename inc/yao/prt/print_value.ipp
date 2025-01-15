#ifndef __YAO__PRT__PRINT_VALUE__IPP__
#define __YAO__PRT__PRINT_VALUE__IPP__

#include "yao/prt/print_value.hpp"

#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"

namespace yao::prt {

template <typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, schar> || std::same_as<T, uchar> ||
           std::same_as<T, short> || std::same_as<T, ushort> ||
           std::same_as<T, int> || std::same_as<T, uint> ||
           std::same_as<T, long> || std::same_as<T, ulong> ||
           std::same_as<T, llong> || std::same_as<T, ullong>
void print_value(std::ostream &os, T t, const PrintValueArgs &, uint) {
  print_type<T>(os);
  os << ": ";
  if constexpr (std::same_as<T, bool>)
    os << (t ? "true" : "false");
  else if constexpr (std::same_as<T, char>) {
    auto hex = [](int val) -> char {
      int low = val & 0x0F;
      return char((low < 10 ? '0' : 'A' - 10) + low);
    };
    os << "0x" << hex(t >> 4) << hex(t);
  } else if constexpr (std::same_as<T, schar> || std::same_as<T, uchar>)
    os << int{t};
  else if constexpr (std::same_as<T, short> || std::same_as<T, ushort> ||
                     std::same_as<T, int> || std::same_as<T, uint> ||
                     std::same_as<T, long> || std::same_as<T, ulong> ||
                     std::same_as<T, llong> || std::same_as<T, ullong>)
    os << t;
  else
    static_assert([]() { return false; }());
}

template <typename T>
  requires c_mf_print_value<T>
void print_value(std::ostream &os, const T &obj, const PrintValueArgs &args,
                 uint indent_level) {
  obj.print_value(os, args, indent_level);
}

template <typename T>
  requires req::c_t_std_set<T>
void print_value(std::ostream &os, const T &set, const PrintValueArgs &args,
                 uint indent_level) {
  print_type<T>(os, args.print_type_args);
  os << ':';
  ++indent_level;
  for (auto ite = set.cbegin(), end = set.cend(); ite != end; ite++) {
    os << '\n';
    print_indent(os, indent_level);
    os << "- ";
    print_value(os, *ite, args, indent_level + 1);
  }
}

template <typename T>
  requires req::c_t_std_map<T>
void print_value(std::ostream &os, const T &map, const PrintValueArgs &args,
                 uint indent_level) {
  print_type<T>(os, args.print_type_args);
  os << ':';
  ++indent_level;
  for (auto ite = map.cbegin(), end = map.cend(); ite != end; ite++) {
    os << '\n';
    print_indent(os, indent_level);
    os << "- ";
    ++indent_level;
    print_value(os, ite->first, args, indent_level);
    os << '\n';
    print_indent(os, indent_level);
    print_value(os, ite->second, args, indent_level);
    --indent_level;
  }
}

} // namespace yao::prt

#endif
