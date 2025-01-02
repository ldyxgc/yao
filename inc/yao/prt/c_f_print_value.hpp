#ifndef __YAO__PRT__C_F_PRINT_VALUE__HPP__
#define __YAO__PRT__C_F_PRINT_VALUE__HPP__

#include <ostream>

#include "yao/prt/print_value.hpp"

namespace yao::prt {

// c: concept, f: function
template <typename T>
concept c_f_print_value = requires {
  // // ns: namespace, tp: template
  // template <bool ns, bool tp, typename T>
  // void print_value(std::ostream &os, T t);
  static_cast<void (*)(std::ostream &os, T t)>(print_value<false, false, T>);
} || requires {
  // // ns: namespace, tp: template
  // template <bool ns, bool tp, typename T>
  // void print_value(std::ostream &os, const T &t);
  static_cast<void (*)(std::ostream &os, const T &t)>(
      print_value<false, false, T>);
};

} // namespace yao::prt

#endif
