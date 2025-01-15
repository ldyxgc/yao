#ifndef __YAO__PRT__C_MF_PRINT_VALUE__HPP__
#define __YAO__PRT__C_MF_PRINT_VALUE__HPP__

#include <ostream>

#include "yao/prt/PrintValueArgs.hpp"

namespace yao::prt {

// c: concept, mf: member function
template <typename T>
concept c_mf_print_value = requires {
  // struct T {
  //   void print_value(std::ostream &os, const PrintValueArgs &args) const;
  // };
  static_cast<void (T::*)(std::ostream &os, const PrintValueArgs &args) const>(
      &T::print_value);
};

} // namespace yao::prt

#endif
