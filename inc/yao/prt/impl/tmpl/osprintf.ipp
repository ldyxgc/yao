#ifndef __YAO__PRT__IMPL__TMPL__OSPRINTF__IPP__
#define __YAO__PRT__IMPL__TMPL__OSPRINTF__IPP__

#include "yao/prt/impl/tmpl/osprintf.hpp"

#include <cstdio>

#include "yao/def/claim.hpp"
#include "yao/def/warn.hpp"

namespace yao::prt::impl::tmpl {

void osprintf(std::ostream &os, not_null<czstring> fmt, auto... args) {
  YAO_CLAIM(fmt != nullptr);

  if constexpr (sizeof...(args) == 0) {
    os << fmt;

  } else {
    YAO_WARN_PUSH
    YAO_WARN_OFF__FORMAT_NON_LITERAL
    int res_num = std::snprintf(nullptr, 0, fmt, args...);
    YAO_WARN_POP
    YAO_CLAIM(res_num >= 0);

    unsigned len = static_cast<unsigned>(res_num) + 1u;
    not_null<owner<zstring>> buf = new char[len];
    YAO_CLAIM(buf != nullptr);

    YAO_WARN_PUSH
    YAO_WARN_OFF__FORMAT_NON_LITERAL
    [[maybe_unused]] int res = std::snprintf(buf, len, fmt, args...);
    YAO_WARN_POP
    YAO_CLAIM(res >= 0);

    os << buf;
    delete[] buf;
  }
}

} // namespace yao::prt::impl::tmpl

#endif
