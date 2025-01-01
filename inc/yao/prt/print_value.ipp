#ifndef __YAO__PRT__PRINT_VALUE__IPP__
#define __YAO__PRT__PRINT_VALUE__IPP__

#include "yao/prt/print_value.hpp"

#include <format>

#include "yao/prt/print_type.hpp"

namespace yao::prt {

template <bool ns, bool tp, typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void print_value(std::ostream &os, T t) {
  print_type<T, ns, tp>(os);
  os << ": ";
  if constexpr (std::same_as<T, bool>)
    os << (t ? "true" : "false");
  else if constexpr (std::same_as<T, char>)
    os << std::format("0x{:02X}", t);
  else if constexpr (std::same_as<T, std::int8_t> ||
                     std::same_as<T, std::uint8_t>)
    os << int{t};
  else if constexpr (std::same_as<T, std::int16_t> ||
                     std::same_as<T, std::uint16_t> ||
                     std::same_as<T, std::int32_t> ||
                     std::same_as<T, std::uint32_t> ||
                     std::same_as<T, std::int64_t> ||
                     std::same_as<T, std::uint64_t>)
    os << t;
  else
    static_assert([]() { return false; }());
}

} // namespace yao::prt

#endif
