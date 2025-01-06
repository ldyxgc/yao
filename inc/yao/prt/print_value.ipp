#ifndef __YAO__PRT__PRINT_VALUE__IPP__
#define __YAO__PRT__PRINT_VALUE__IPP__

#include "yao/prt/print_value.hpp"

#include "yao/prt/print_type.hpp"

namespace yao::prt {

template <bool ns, bool tp, typename T>
  requires std::same_as<T, bool> || std::same_as<T, char> ||
           std::same_as<T, std::int8_t> || std::same_as<T, std::uint8_t> ||
           std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
           std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
           std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t>
void print_value(std::ostream &os, T t) {
  print_type<T, ns, tp>(os);
  os << ": ";
  if constexpr (std::same_as<T, bool>)
    os << (t ? "true" : "false");
  else if constexpr (std::same_as<T, char>) {
    auto hex = [](int val) -> char {
      int low = val & 0x0F;
      return char((low < 10 ? '0' : 'A' - 10) + low);
    };
    os << "0x" << hex(t >> 4) << hex(t);
  } else if constexpr (std::same_as<T, std::int8_t> ||
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
  requires c_mf_print_value<T>
void print_value(std::ostream &os, const T &obj) {
  if constexpr (impl::tmpl::c_mf_print_value<T>)
    obj.template print_value<ns, tp>(os);
  else if constexpr (impl::func::c_mf_print_value<T>)
    obj.print_value(os, ns, tp);
  else
    static_assert([]() { return false; }());
}

template <bool ns, bool tp, typename T>
  requires req::c_t_std_set<T>
void print_value(std::ostream &os, const T &set) {
  print_type<T, ns, tp>(os);
  os << ": {";
  {
    auto ite = set.cbegin(), end = set.cend();
    std::size_t idx = 0;
    while (ite != end) {
      if (idx)
        os << ',';
      os << idx << ':';
      print_value<ns, tp>(os, *ite);
      ite++;
      idx++;
    }
  }
  os << '}';
}

template <bool ns, bool tp, typename T>
  requires req::c_t_std_map<T>
void print_value(std::ostream &os, const T &map) {
  print_type<T, ns, tp>(os);
  os << ": {";
  {
    auto ite = map.cbegin(), end = map.cend();
    std::size_t idx = 0;
    while (ite != end) {
      if (idx)
        os << ',';
      os << idx << ": {";
      print_value<ns, tp>(os, ite->first);
      os << ',';
      print_value<ns, tp>(os, ite->second);
      os << '}';
      ite++;
      idx++;
    }
  }
  os << '}';
}

template <bool ns, bool tp, typename T>
  requires req::c_t_std_unique_ptr<T>
void print_value(std::ostream &os, const T &uptr) {
  print_type<T, ns, tp>(os);
  os << ": {";
  if (uptr)
    print_value<ns, tp>(os, *uptr);
  os << '}';
}

template <bool ns, bool tp, typename T>
  requires req::c_t_std_shared_ptr<T>
void print_value(std::ostream &os, const T &sptr) {
  print_type<T, ns, tp>(os);
  os << ": {";
  if (sptr)
    print_value<ns, tp>(os, *sptr);
  os << '}';
}

} // namespace yao::prt

#endif
