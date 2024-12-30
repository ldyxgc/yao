#ifndef __YAO__PRT__IMPL__FUNC__PRINT_FORMAT__HPP__
#define __YAO__PRT__IMPL__FUNC__PRINT_FORMAT__HPP__

#include <ostream>

#include "yao/com.hpp"

namespace yao::prt::impl::func {

void print_format(std::ostream &os, not_null<czstring> fmt, ...);

} // namespace yao::prt::impl::func

#endif
