#ifndef __YAO__LAB__PRT__OSPRINT_TYPE__HPP__
#define __YAO__LAB__PRT__OSPRINT_TYPE__HPP__

#include <concepts>
#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/lab/prt/c_smf_osprint_type.hpp"

namespace yao::lab::prt {

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, bool> || std::same_as<T, char>
void osprint_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void osprint_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires c_smf_osprint_type<T>
void osprint_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, std::set<typename T::key_type>>
void osprint_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T,
                        std::map<typename T::key_type, typename T::mapped_type>>
void osprint_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, std::unique_ptr<typename T::element_type>>
void osprint_type(std::ostream &os);

// ns: namespace, tp: template
template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, std::shared_ptr<typename T::element_type>>
void osprint_type(std::ostream &os);

} // namespace yao::lab::prt

#include "yao/lab/prt/osprint_type.ipp"

#endif
