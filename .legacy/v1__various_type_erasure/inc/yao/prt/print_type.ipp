#ifndef __YAO__PRT__PRINT_TYPE__IPP__
#define __YAO__PRT__PRINT_TYPE__IPP__

#include "yao/prt/print_type.hpp"

#include <type_traits>

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
  requires std::same_as<T, signed char> || std::same_as<T, unsigned char> ||
           std::same_as<T, short> || std::same_as<T, unsigned short> ||
           std::same_as<T, int> || std::same_as<T, unsigned> ||
           std::same_as<T, long> || std::same_as<T, unsigned long> ||
           std::same_as<T, long long> || std::same_as<T, unsigned long long>
void print_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  if constexpr (std::is_unsigned_v<T>)
    os << 'u';
  if constexpr (sizeof(T) == sizeof(std::int8_t))
    os << "int8_t";
  else if constexpr (sizeof(T) == sizeof(std::int16_t))
    os << "int16_t";
  else if constexpr (sizeof(T) == sizeof(std::int32_t))
    os << "int32_t";
  else if constexpr (sizeof(T) == sizeof(std::int64_t))
    os << "int64_t";
  else
    static_assert([]() { return false; }());
}

template <typename T, bool ns, bool tp>
  requires c_smf_print_type<T>
void print_type(std::ostream &os) {
  T::template print_type<ns, tp>(os);
}

template <typename T, bool ns, bool tp>
  requires req::c_t_std_set<T>
void print_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "set";
  if constexpr (tp) {
    os << '<';
    print_type<typename T::key_type, ns, tp>(os);
    os << '>';
  }
}

template <typename T, bool ns, bool tp>
  requires req::c_t_std_map<T>
void print_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "map";
  if constexpr (tp) {
    os << '<';
    print_type<typename T::key_type, ns, tp>(os);
    os << '|';
    print_type<typename T::mapped_type, ns, tp>(os);
    os << '>';
  }
}

template <typename T, bool ns, bool tp>
  requires req::c_t_std_unique_ptr<T>
void print_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "unique_ptr";
  if constexpr (tp) {
    os << '<';
    print_type<typename T::element_type, ns, tp>(os);
    os << '>';
  }
}

template <typename T, bool ns, bool tp>
  requires req::c_t_std_shared_ptr<T>
void print_type(std::ostream &os) {
  if constexpr (ns)
    os << "std::";
  os << "shared_ptr";
  if constexpr (tp) {
    os << '<';
    print_type<typename T::element_type, ns, tp>(os);
    os << '>';
  }
}

} // namespace yao::prt

#endif
