#ifndef __YAO__PRT__PRINT_VALUE__IPP__
#define __YAO__PRT__PRINT_VALUE__IPP__

#include "yao/prt/print_value.hpp"

#include "yao/prt/print_type.hpp"

namespace yao::prt {

template <typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, schar> || std::same_as<T, uchar> ||
           std::same_as<T, short> || std::same_as<T, ushort> ||
           std::same_as<T, int> || std::same_as<T, uint> ||
           std::same_as<T, long> || std::same_as<T, ulong> ||
           std::same_as<T, llong> || std::same_as<T, ullong>
void print_value(std::ostream &os, T t, const PrintValueArgs &) {
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

} // namespace yao::prt

#endif
