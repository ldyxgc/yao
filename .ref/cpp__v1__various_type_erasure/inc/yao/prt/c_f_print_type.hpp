#ifndef __YAO__PRT__C_F_PRINT_TYPE__HPP__
#define __YAO__PRT__C_F_PRINT_TYPE__HPP__

#include <ostream>

#include "yao/prt/print_type.hpp"

namespace yao::prt {

// c: concept, f: function
template <typename T>
concept c_f_print_type = requires {
  // // ns: namespace, tp: template
  // template <typename T, bool ns, bool tp>
  // void print_type(std::ostream &os);
  static_cast<void (*)(std::ostream &)>(print_type<T, false, false>);
};

} // namespace yao::prt

#endif
