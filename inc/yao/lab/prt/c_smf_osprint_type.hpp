#ifndef __YAO__LAB__PRT__C_SMF_OSPRINT_TYPE__HPP__
#define __YAO__LAB__PRT__C_SMF_OSPRINT_TYPE__HPP__

#include <ostream>

namespace yao::lab::prt {

// c: concept, smf: static member function
template <typename T>
concept c_smf_osprint_type = requires {
  // struct T {
  //   template <bool ns, bool tp>
  //   static void osprint_type(std::ostream &os);
  // };
  static_cast<void (*)(std::ostream &os)>(T::template osprint_type<0, 0>);
};

} // namespace yao::lab::prt

#endif
