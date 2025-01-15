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

template <typename T>
  requires c_smf_print_type<T>
void print_type(std::ostream &os, const PrintTypeArgs &args) {
  T::print_type(os, args);
}

template <typename T>
  requires req::c_t_std_set<T>
void print_type(std::ostream &os, const PrintTypeArgs &args) {
  if (args.scope)
    os << "std::";
  os << "set";
  if (args.tmpl_args) {
    os << '<';
    print_type<typename T::key_type>(os, args);
    os << '>';
  }
}

template <typename T>
  requires req::c_t_std_map<T>
void print_type(std::ostream &os, const PrintTypeArgs &args) {
  if (args.scope)
    os << "std::";
  os << "map";
  if (args.tmpl_args) {
    os << '<';
    print_type<typename T::key_type>(os, args);
    os << ',';
    print_type<typename T::mapped_type>(os, args);
    os << '>';
  }
}

} // namespace yao::prt

#endif
