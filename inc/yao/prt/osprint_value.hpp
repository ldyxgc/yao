#ifndef __YAO__PRT__OSPRINT_VALUE__HPP__
#define __YAO__PRT__OSPRINT_VALUE__HPP__

#include <concepts>
#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/prt/c_mf_osprint_value.hpp"

namespace yao::prt {

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void osprint_value(std::ostream &os, T t);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires c_mf_osprint_value<T>
void osprint_value(std::ostream &os, const T &obj);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, std::set<typename T::key_type>>
void osprint_value(std::ostream &os, const T &set);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T,
                        std::map<typename T::key_type, typename T::mapped_type>>
void osprint_value(std::ostream &os, const T &map);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, std::unique_ptr<typename T::element_type>>
void osprint_value(std::ostream &os, const T &uptr);

// ns: namespace, tp: template
template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, std::shared_ptr<typename T::element_type>>
void osprint_value(std::ostream &os, const T &sptr);

} // namespace yao::prt

#include "yao/prt/osprint_value.ipp"

#endif
