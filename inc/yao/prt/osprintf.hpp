#ifndef __YAO__PRT__OSPRINTF__HPP__
#define __YAO__PRT__OSPRINTF__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__OSPRINTF == YAO_CONFIG__OSPRINTF__FUNCTION

#include "yao/prt/impl/func/osprintf.hpp"

namespace yao::prt {

constexpr auto osprintf = impl::func::osprintf;

} // namespace yao::prt

#elif YAO_CONFIG__OSPRINTF == YAO_CONFIG__OSPRINTF__TEMPLATE

#include <ostream>

#include "yao/help.hpp"
#include "yao/prt/impl/tmpl/osprintf.hpp"

namespace yao::prt {

void osprintf(std::ostream &os, not_null<czstring> fmt, auto... args) {
  impl::tmpl::osprintf(os, fmt, args...);
}

} // namespace yao::prt

#endif

#endif
