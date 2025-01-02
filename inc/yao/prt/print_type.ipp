#ifndef __YAO__PRT__PRINT_TYPE__IPP__
#define __YAO__PRT__PRINT_TYPE__IPP__

#include "yao/prt/print_type.hpp"

namespace yao::prt {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, bool> || std::same_as<T, char>
void print_type(std::ostream &os) {
  if constexpr (std::same_as<T, bool>)
    os << "bool";
  else if constexpr (std::same_as<T, char>)
    os << "char";
  else
    static_assert([]() { return false; }());
}

template <typename T, bool ns, bool tp>
  requires std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void print_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  if constexpr (std::same_as<T, std::int8_t>)
    os << "int8_t";
  else if constexpr (std::same_as<T, std::uint8_t>)
    os << "uint8_t";
  else if constexpr (std::same_as<T, std::int16_t>)
    os << "int16_t";
  else if constexpr (std::same_as<T, std::uint16_t>)
    os << "uint16_t";
  else if constexpr (std::same_as<T, std::int32_t>)
    os << "int32_t";
  else if constexpr (std::same_as<T, std::uint32_t>)
    os << "uint32_t";
  else if constexpr (std::same_as<T, std::int64_t>)
    os << "int64_t";
  else if constexpr (std::same_as<T, std::uint64_t>)
    os << "uint64_t";
  else
    static_assert([]() { return false; }());
}

template <typename T, bool ns, bool tp>
  requires c_smf_print_type<T>
void print_type(std::ostream &os) {
  T::template print_type<ns, tp>(os);
}

} // namespace yao::prt

#endif
