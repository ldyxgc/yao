#ifndef __YAO__PRT__C_F_PRINT_VALUE__HPP__
#define __YAO__PRT__C_F_PRINT_VALUE__HPP__

#include <ostream>

#include "yao/com.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::prt {

// c: concept, f: function
template <typename T>
concept c_f_print_value = requires {
  // template <typename T>
  // void print_value(std::ostream &os, T t, const PrintValueArgs &args,
  //                  uint indent_level);
  static_cast<void (*)(std::ostream &os, T t, const PrintValueArgs &args,
                       uint indent_level)>(print_value<T>);
} || requires {
  // template <typename T>
  // void print_value(std::ostream &os, const T &t, const PrintValueArgs &args,
  //                  uint indent_level);
  static_cast<void (*)(std::ostream &os, const T &t, const PrintValueArgs &args,
                       uint indent_level)>(print_value<T>);
};

} // namespace yao::prt

#endif
