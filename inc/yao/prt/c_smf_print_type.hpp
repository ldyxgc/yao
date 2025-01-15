#ifndef __YAO__PRT__C_SMF_PRINT_TYPE__HPP__
#define __YAO__PRT__C_SMF_PRINT_TYPE__HPP__

#include <ostream>

#include "yao/prt/PrintTypeArgs.hpp"

namespace yao::prt {

// c: concept, smf: static member function
template <typename T>
concept c_smf_print_type = requires {
  // struct T {
  //   static void print_type(std::ostream &os, const PrintTypeArgs &args);
  // };
  static_cast<void (*)(std::ostream &os, const PrintTypeArgs &args)>(
      T::print_type);
};

} // namespace yao::prt

#endif
