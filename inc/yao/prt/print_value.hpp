#ifndef __YAO__PRT__PRINT_VALUE__HPP__
#define __YAO__PRT__PRINT_VALUE__HPP__

#include <concepts>
#include <ostream>

#include "yao/com.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/c_mf_print_value.hpp"
#include "yao/req/c_t_std_map.hpp"
#include "yao/req/c_t_std_set.hpp"

namespace yao::prt {

template <typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, schar> || std::same_as<T, uchar> ||
           std::same_as<T, short> || std::same_as<T, ushort> ||
           std::same_as<T, int> || std::same_as<T, uint> ||
           std::same_as<T, long> || std::same_as<T, ulong> ||
           std::same_as<T, llong> || std::same_as<T, ullong>
void print_value(std::ostream &os, T t, const PrintValueArgs &args = {},
                 uint indent_level = 0);

template <typename T>
  requires c_mf_print_value<T>
void print_value(std::ostream &os, const T &obj,
                 const PrintValueArgs &args = {}, uint indent_level = 0);

template <typename T>
  requires req::c_t_std_set<T>
void print_value(std::ostream &os, const T &set,
                 const PrintValueArgs &args = {}, uint indent_level = 0);

template <typename T>
  requires req::c_t_std_map<T>
void print_value(std::ostream &os, const T &map,
                 const PrintValueArgs &args = {}, uint indent_level = 0);

} // namespace yao::prt

#include "yao/prt/print_value.ipp"

#endif
