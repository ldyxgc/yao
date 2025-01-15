#ifndef __YAO__PRT__PRINT_TYPE__IPP__
#define __YAO__PRT__PRINT_TYPE__IPP__

#include "yao/prt/print_type.hpp"

namespace yao::prt {

template <typename T>
  requires std::same_as<T, bool> || std::same_as<T, char>
void print_type(std::ostream &os, const PrintTypeArgs &) {
  if constexpr (std::same_as<T, bool>)
    os << "bool";
  else if constexpr (std::same_as<T, char>)
    os << "char";
  else
    static_assert([]() { return false; }());
}

template <typename T>
  requires std::same_as<T, schar> || std::same_as<T, uchar> ||
           std::same_as<T, short> || std::same_as<T, ushort> ||
           std::same_as<T, int> || std::same_as<T, uint> ||
           std::same_as<T, long> || std::same_as<T, ulong> ||
           std::same_as<T, llong> || std::same_as<T, ullong>
void print_type(std::ostream &os, const PrintTypeArgs &) {
  if constexpr (std::same_as<T, schar>)
    os << "schar";
  else if constexpr (std::same_as<T, uchar>)
    os << "uchar";
  else if constexpr (std::same_as<T, short>)
    os << "short";
  else if constexpr (std::same_as<T, ushort>)
    os << "ushort";
  else if constexpr (std::same_as<T, int>)
    os << "int";
  else if constexpr (std::same_as<T, uint>)
    os << "uint";
  else if constexpr (std::same_as<T, long>)
    os << "long";
  else if constexpr (std::same_as<T, ulong>)
    os << "ulong";
  else if constexpr (std::same_as<T, llong>)
    os << "llong";
  else if constexpr (std::same_as<T, ullong>)
    os << "ullong";
  else
    static_assert([]() { return false; }());
}

} // namespace yao::prt

#endif
