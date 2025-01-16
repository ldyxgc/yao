#ifndef __YAO__PRT__PRINT_TYPE__HPP__
#define __YAO__PRT__PRINT_TYPE__HPP__

#include <concepts>
#include <ostream>

#include "yao/com.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/c_smf_print_type.hpp"
#include "yao/req/c_t_std_map.hpp"
#include "yao/req/c_t_std_set.hpp"
#include "yao/req/c_t_std_shared_ptr.hpp"
#include "yao/req/c_t_std_unique_ptr.hpp"

namespace yao::prt {

template <typename T>
  requires std::same_as<T, bool> || std::same_as<T, char>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

template <typename T>
  requires std::same_as<T, schar> || std::same_as<T, uchar> ||
           std::same_as<T, short> || std::same_as<T, ushort> ||
           std::same_as<T, int> || std::same_as<T, uint> ||
           std::same_as<T, long> || std::same_as<T, ulong> ||
           std::same_as<T, llong> || std::same_as<T, ullong>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

template <typename T>
  requires c_smf_print_type<T>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

template <typename T>
  requires req::c_t_std_set<T>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

template <typename T>
  requires req::c_t_std_map<T>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

template <typename T>
  requires req::c_t_std_unique_ptr<T>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

template <typename T>
  requires req::c_t_std_shared_ptr<T>
void print_type(std::ostream &os, const PrintTypeArgs &args = {});

} // namespace yao::prt

#include "yao/prt/print_type.ipp"

#endif
