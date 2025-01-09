#ifndef __YAO__PRT__C_MF_PRINT_VALUE__HPP__
#define __YAO__PRT__C_MF_PRINT_VALUE__HPP__

#include <ostream>

namespace yao::prt {

namespace impl {

namespace tmpl {

// c: concept, mf: member function
template <typename T>
concept c_mf_print_value = requires {
  // struct T {
  //   // ns: namespace, tp: template
  //   template <bool ns, bool tp>
  //   void print_value(std::ostream &os) const;
  // };
  static_cast<void (T::*)(std::ostream &os) const>(
      &T::template print_value<false, false>);
};

} // namespace tmpl

namespace func {

// c: concept, mf: member function
template <typename T>
concept c_mf_print_value = requires {
  // struct T {
  //   // ns: namespace, tp: template
  //   void print_value(std::ostream &os, bool ns, bool tp) const;
  // };
  static_cast<void (T::*)(std::ostream &os, bool ns, bool tp) const>(
      &T::print_value);
};

} // namespace func

} // namespace impl

// c: concept, mf: member function
template <typename T>
concept c_mf_print_value =
    impl::tmpl::c_mf_print_value<T> || impl::func::c_mf_print_value<T>;

} // namespace yao::prt

#endif
