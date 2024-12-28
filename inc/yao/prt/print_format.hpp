#ifndef __YAO__PRT__PRINT_FORMAT__HPP__
#define __YAO__PRT__PRINT_FORMAT__HPP__

#include <ostream>

#include "yao/com.hpp"

namespace yao::prt {

void print_format(std::ostream &os, not_null<czstring> fmt, ...);

} // namespace yao::prt

#endif
