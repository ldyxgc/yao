#ifndef __YAO__PRT__C_SMF_PRINT_TYPE__HPP__
#define __YAO__PRT__C_SMF_PRINT_TYPE__HPP__

#include <ostream>

namespace yao::prt {

// c: concept, smf: static member function
template <typename T>
concept c_smf_print_type = requires {
  // struct T {
  //   // ns: namespace, tp: template
  //   template <bool ns, bool tp>
  //   static void print_type(std::ostream &os);
  // };
  static_cast<void (*)(std::ostream &os)>(T::template print_type<false, false>);
};

} // namespace yao::prt

#endif
