#ifndef __YAO__PRT__PRINT_FORMAT__HPP__
#define __YAO__PRT__PRINT_FORMAT__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__PRINT_FORMAT == YAO_CONFIG__PRINT_FORMAT__FUNCTION

#include "yao/prt/impl/func/print_format.hpp"

namespace yao::prt {

constexpr auto print_format = impl::func::print_format;

} // namespace yao::prt

#elif YAO_CONFIG__PRINT_FORMAT == YAO_CONFIG__PRINT_FORMAT__TEMPLATE

#include <ostream>

#include "yao/com.hpp"
#include "yao/prt/impl/tmpl/print_format.hpp"

namespace yao::prt {

void print_format(std::ostream &os, not_null<czstring> fmt, auto... args) {
  impl::tmpl::print_format(os, fmt, args...);
}

} // namespace yao::prt

#endif

#endif
