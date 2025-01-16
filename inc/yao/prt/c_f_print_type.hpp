#ifndef __YAO__PRT__C_F_PRINT_TYPE__HPP__
#define __YAO__PRT__C_F_PRINT_TYPE__HPP__

#include <ostream>

#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/print_type.hpp"

namespace yao::prt {

// c: concept, f: function
template <typename T>
concept c_f_print_type = requires {
  // template <typename T>
  // void print_type(std::ostream &os, const PrintTypeArgs &args);
  static_cast<void (*)(std::ostream &os, const PrintTypeArgs &args)>(
      print_type<T>);
};

} // namespace yao::prt

#endif
