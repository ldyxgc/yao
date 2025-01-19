#ifndef __YAO__PRT__PRINT_INDENT__HPP__
#define __YAO__PRT__PRINT_INDENT__HPP__

#include <ostream>

#include "yao/com.hpp"

namespace yao::prt {

inline void print_indent(std::ostream &os, uint indent_level) {
  while (indent_level--)
    os << "  ";
}

} // namespace yao::prt

#endif
