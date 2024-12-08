#ifndef __YAO__PRT__OSPRINTF__HPP__
#define __YAO__PRT__OSPRINTF__HPP__

#include <ostream>

namespace yao::prt {

void osprintf(std::ostream &os, const char *fmt, ...);

} // namespace yao::prt

#endif
