#ifndef __YAO__PRT__PRINT_VALUE__HPP__
#define __YAO__PRT__PRINT_VALUE__HPP__

#include <concepts>
#include <cstdint>
#include <ostream>

#include "yao/prt/c_mf_print_value.hpp"

namespace yao::prt {

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void print_value(std::ostream &os, T t);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires c_mf_print_value<T>
void print_value(std::ostream &os, const T &obj);

} // namespace yao::prt

#include "yao/prt/print_value.ipp"

#endif
