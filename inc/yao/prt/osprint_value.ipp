#ifndef __YAO__PRT__OSPRINT_VALUE__IPP__
#define __YAO__PRT__OSPRINT_VALUE__IPP__

#include "yao/prt/osprint_value.hpp"

#include "yao/prt/osprint_type.hpp"
#include "yao/prt/osprintf.hpp"

namespace yao::prt {

template <bool ns, bool tp, typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void osprint_value(std::ostream &os, T t) {
  osprint_type<T, ns, tp>(os);
  os << ": ";
  if constexpr (std::same_as<T, bool>)
    os << (t ? "true" : "false");
  else if constexpr (std::same_as<T, char>)
    osprintf(os, "0x%02X", static_cast<std::uint8_t>(t));
  else if constexpr (std::same_as<T, std::int8_t> ||
                     std::same_as<T, std::uint8_t>)
    os << int{t};
  else if constexpr (std::same_as<T, std::int16_t> ||
                     std::same_as<T, std::uint16_t> ||
                     std::same_as<T, std::int32_t> ||
                     std::same_as<T, std::uint32_t> ||
                     std::same_as<T, std::int64_t> ||
                     std::same_as<T, std::uint64_t>)
    os << t;
  else
    static_assert([]() { return false; }());
}

template <bool ns, bool tp, typename T>
  requires c_mf_osprint_value<T>
void osprint_value(std::ostream &os, const T &obj) {
  if constexpr (impl::tmpl::c_mf_osprint_value<T>)
    obj.template osprint_value<ns, tp>(os);
  else if constexpr (impl::func::c_mf_osprint_value<T>)
    obj.osprint_value(os, ns, tp);
  else
    static_assert([]() { return false; }());
}

template <bool ns, bool tp, typename T>
  requires std::same_as<T, std::set<typename T::key_type>>
void osprint_value(std::ostream &os, const T &set) {
  osprint_type<T, ns, tp>(os);
  os << ": {";
  {
    auto ite = set.cbegin(), end = set.cend();
    std::size_t idx = 0;
    while (ite != end) {
      if (idx)
        os << ',';
      os << idx << ':';
      osprint_value<ns, tp>(os, *ite);
      ite++;
      idx++;
    }
  }
  os << '}';
}

template <bool ns, bool tp, typename T>
  requires std::same_as<T,
                        std::map<typename T::key_type, typename T::mapped_type>>
void osprint_value(std::ostream &os, const T &map) {
  osprint_type<T, ns, tp>(os);
  os << ": {";
  {
    auto ite = map.cbegin(), end = map.cend();
    std::size_t idx = 0;
    while (ite != end) {
      if (idx)
        os << ',';
      os << idx << ": {";
      osprint_value<ns, tp>(os, ite->first);
      os << ',';
      osprint_value<ns, tp>(os, ite->second);
      os << '}';
      ite++;
      idx++;
    }
  }
  os << '}';
}

template <bool ns, bool tp, typename T>
  requires std::same_as<T, std::unique_ptr<typename T::element_type>>
void osprint_value(std::ostream &os, const T &uptr) {
  osprint_type<T, ns, tp>(os);
  os << ": {";
  if (uptr)
    osprint_value<ns, tp>(os, *uptr);
  os << '}';
}

template <bool ns, bool tp, typename T>
  requires std::same_as<T, std::shared_ptr<typename T::element_type>>
void osprint_value(std::ostream &os, const T &sptr) {
  osprint_type<T, ns, tp>(os);
  os << ": {";
  if (sptr)
    osprint_value<ns, tp>(os, *sptr);
  os << '}';
}

} // namespace yao::prt

#endif
