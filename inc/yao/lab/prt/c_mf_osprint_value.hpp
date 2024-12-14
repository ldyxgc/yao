#ifndef __YAO__LAB__PRT__C_MF_OSPRINT_VALUE__HPP__
#define __YAO__LAB__PRT__C_MF_OSPRINT_VALUE__HPP__

#include <ostream>

namespace yao::lab::prt {

namespace impl {

namespace tmpl {

// c: concept, mf: member function
template <typename T>
concept c_mf_osprint_value = requires {
  // struct T {
  //   template <bool ns, bool tp>
  //   void osprint_value(std::ostream &os) const;
  // };
  static_cast<void (T::*)(std::ostream &os) const>(
      &T::template osprint_value<0, 0>);
};

} // namespace tmpl

namespace func {

// c: concept, mf: member function
template <typename T>
concept c_mf_osprint_value = requires {
  // struct T {
  //   void osprint_value(std::ostream &os, bool ns, bool tp) const;
  // };
  static_cast<void (T::*)(std::ostream &os, bool ns, bool tp) const>(
      &T::osprint_value);
};

} // namespace func

} // namespace impl

// c: concept, mf: member function
template <typename T>
concept c_mf_osprint_value =
    impl::tmpl::c_mf_osprint_value<T> || impl::func::c_mf_osprint_value<T>;

} // namespace yao::lab::prt

#endif
