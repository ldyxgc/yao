#include "yao/prt/impl/func/osprintf.hpp"

#include <cstdarg>
#include <cstdio>

#include "yao/def/claim.hpp"
#include "yao/def/warn.hpp"

namespace yao::prt::impl::func {

void osprintf(std::ostream &os, not_null<czstring> fmt, ...) {
  YAO_CLAIM(fmt != nullptr);
  std::va_list args;

  va_start(args, fmt);
  YAO_WARN_PUSH
  YAO_WARN_OFF__FORMAT_NON_LITERAL
  int res_num = std::vsnprintf(nullptr, 0, fmt, args);
  YAO_WARN_POP
  va_end(args);
  YAO_CLAIM(res_num >= 0);

  unsigned len = static_cast<unsigned>(res_num) + 1u;
  not_null<owner<zstring>> buf = new char[len];
  YAO_CLAIM(buf != nullptr);

  va_start(args, fmt);
  YAO_WARN_PUSH
  YAO_WARN_OFF__FORMAT_NON_LITERAL
  [[maybe_unused]] int res = std::vsnprintf(buf, len, fmt, args);
  YAO_WARN_POP
  va_end(args);
  YAO_CLAIM(res >= 0);

  os << buf;
  delete[] buf;
}

} // namespace yao::prt::impl::func
