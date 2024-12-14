#ifndef __YAO__LAB__PRT__C_F_OSPRINT_VALUE__HPP__
#define __YAO__LAB__PRT__C_F_OSPRINT_VALUE__HPP__

#include <ostream>

#include "yao/lab/prt/osprint_value.hpp"

namespace yao::lab::prt {

// c: concept, f: function
template <typename T>
concept c_f_osprint_value = requires {
  // template <bool ns, bool tp, typename T>
  // void osprint_value(std::ostream &os, T t);
  static_cast<void (*)(std::ostream &os, T t)>(osprint_value<0, 0, T>);
} || requires {
  // template <bool ns, bool tp, typename T>
  // void osprint_value(std::ostream &os, const T &t);
  static_cast<void (*)(std::ostream &os, const T &t)>(osprint_value<0, 0, T>);
};

} // namespace yao::lab::prt

#endif
