#ifndef __YAO__PRT__IMPL__TMPL__OSPRINTF__HPP__
#define __YAO__PRT__IMPL__TMPL__OSPRINTF__HPP__

#include <ostream>

#include "yao/help.hpp"

namespace yao::prt::impl::tmpl {

void osprintf(std::ostream &os, not_null<czstring> fmt, auto... args);

} // namespace yao::prt::impl::tmpl

#include "yao/prt/impl/tmpl/osprintf.ipp"

#endif
