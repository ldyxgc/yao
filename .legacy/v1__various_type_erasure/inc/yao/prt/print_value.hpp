#ifndef __YAO__PRT__PRINT_VALUE__HPP__
#define __YAO__PRT__PRINT_VALUE__HPP__

#include <concepts>
#include <cstdint>
#include <ostream>

#include "yao/prt/c_mf_print_value.hpp"
#include "yao/req/c_t_std_map.hpp"
#include "yao/req/c_t_std_set.hpp"
#include "yao/req/c_t_std_shared_ptr.hpp"
#include "yao/req/c_t_std_unique_ptr.hpp"

namespace yao::prt {

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, signed char> || std::same_as<T, unsigned char> ||
           std::same_as<T, short> || std::same_as<T, unsigned short> ||
           std::same_as<T, int> || std::same_as<T, unsigned> ||
           std::same_as<T, long> || std::same_as<T, unsigned long> ||
           std::same_as<T, long long> || std::same_as<T, unsigned long long>
void print_value(std::ostream &os, T t);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires c_mf_print_value<T>
void print_value(std::ostream &os, const T &obj);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires req::c_t_std_set<T>
void print_value(std::ostream &os, const T &set);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires req::c_t_std_map<T>
void print_value(std::ostream &os, const T &map);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires req::c_t_std_unique_ptr<T>
void print_value(std::ostream &os, const T &uptr);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires req::c_t_std_shared_ptr<T>
void print_value(std::ostream &os, const T &sptr);

} // namespace yao::prt

#include "yao/prt/print_value.ipp"

#endif
