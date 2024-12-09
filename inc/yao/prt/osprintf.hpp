#ifndef __YAO__PRT__OSPRINTF__HPP__
#define __YAO__PRT__OSPRINTF__HPP__

#include <ostream>

#include "yao/help.hpp"

namespace yao::prt {

void osprintf(std::ostream &os, not_null<czstring> fmt, ...);

} // namespace yao::prt

#endif
