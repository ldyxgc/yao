#ifndef __YAO__LAB__PRT__OSPRINT_TYPE__IPP__
#define __YAO__LAB__PRT__OSPRINT_TYPE__IPP__

#include "yao/lab/prt/osprint_type.hpp"

namespace yao::lab::prt {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, bool> || std::same_as<T, char>
void osprint_type(std::ostream &os) {
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
void osprint_type(std::ostream &os) {
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
  requires c_smf_osprint_type<T>
void osprint_type(std::ostream &os) {
  T::template osprint_type<ns, tp>(os);
}

template <typename T, bool ns, bool tp>
  requires std::same_as<T, std::set<typename T::key_type>>
void osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "set";
  if constexpr (tp) {
    os << '<';
    osprint_type<typename T::key_type, ns, tp>(os);
    os << '>';
  }
}

template <typename T, bool ns, bool tp>
  requires std::same_as<T,
                        std::map<typename T::key_type, typename T::mapped_type>>
void osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "map";
  if constexpr (tp) {
    os << '<';
    osprint_type<typename T::key_type, ns, tp>(os);
    os << '|';
    osprint_type<typename T::mapped_type, ns, tp>(os);
    os << '>';
  }
}

template <typename T, bool ns, bool tp>
  requires std::same_as<T, std::unique_ptr<typename T::element_type>>
void osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "unique_ptr";
  if constexpr (tp) {
    os << '<';
    osprint_type<typename T::element_type, ns, tp>(os);
    os << '>';
  }
}

template <typename T, bool ns, bool tp>
  requires std::same_as<T, std::shared_ptr<typename T::element_type>>
void osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "shared_ptr";
  if constexpr (tp) {
    os << '<';
    osprint_type<typename T::element_type, ns, tp>(os);
    os << '>';
  }
}

} // namespace yao::lab::prt

#endif
