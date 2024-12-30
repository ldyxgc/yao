#ifndef __YAO__PRT__IMPL__TMPL__PRINT_FORMAT__HPP__
#define __YAO__PRT__IMPL__TMPL__PRINT_FORMAT__HPP__

#include <ostream>

#include "yao/com.hpp"

namespace yao::prt::impl::tmpl {

void print_format(std::ostream &os, not_null<czstring> fmt, auto... args);

} // namespace yao::prt::impl::tmpl

#include "yao/prt/impl/tmpl/print_format.ipp"

#endif
