#ifndef __YAO__PRT__C_MF_PRINT_VALUE__HPP__
#define __YAO__PRT__C_MF_PRINT_VALUE__HPP__

#include <ostream>

namespace yao::prt {

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

} // namespace yao::prt

#endif
