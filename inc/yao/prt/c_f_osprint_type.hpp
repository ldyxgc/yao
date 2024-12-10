#ifndef __YAO__PRT__C_F_OSPRINT_TYPE__HPP__
#define __YAO__PRT__C_F_OSPRINT_TYPE__HPP__

#include <ostream>

#include "yao/prt/osprint_type.hpp"

namespace yao::prt {

// c: concept, f: function
template <typename T>
concept c_f_osprint_type = requires {
  // template <typename T, bool ns, bool tp>
  // void osprint_type(std::ostream &os);
  static_cast<void (*)(std::ostream &)>(osprint_type<T, 0, 0>);
};

} // namespace yao::prt

#endif
