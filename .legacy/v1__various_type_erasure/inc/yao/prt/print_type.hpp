#ifndef __YAO__PRT__PRINT_TYPE__HPP__
#define __YAO__PRT__PRINT_TYPE__HPP__

#include <concepts>
#include <cstdint>
#include <ostream>

#include "yao/prt/c_smf_print_type.hpp"
#include "yao/req/c_t_std_map.hpp"
#include "yao/req/c_t_std_set.hpp"
#include "yao/req/c_t_std_shared_ptr.hpp"
#include "yao/req/c_t_std_unique_ptr.hpp"

namespace yao::prt {

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, bool> || std::same_as<T, char>
void print_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, signed char> || std::same_as<T, unsigned char> ||
           std::same_as<T, short> || std::same_as<T, unsigned short> ||
           std::same_as<T, int> || std::same_as<T, unsigned> ||
           std::same_as<T, long> || std::same_as<T, unsigned long> ||
           std::same_as<T, long long> || std::same_as<T, unsigned long long>
void print_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires c_smf_print_type<T>
void print_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires req::c_t_std_set<T>
void print_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires req::c_t_std_map<T>
void print_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires req::c_t_std_unique_ptr<T>
void print_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires req::c_t_std_shared_ptr<T>
void print_type(std::ostream &os);

} // namespace yao::prt

#include "yao/prt/print_type.ipp"

#endif
