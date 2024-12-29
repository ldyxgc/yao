#include "yao/prt/print_format.hpp"

#include <cstdarg>
#include <cstdio>
#include <vector>

#include "yao/def/claim.hpp"
#include "yao/def/warn.hpp"

namespace yao::prt {

void print_format(std::ostream &os, not_null<czstring> fmt, ...) {
  YAO_CLAIM(fmt != nullptr);
  std::va_list args;

  va_start(args, fmt);
  YAO_WARN_PUSH
  YAO_WARN_OFF__FORMAT_NON_LITERAL
  int res_num = std::vsnprintf(nullptr, 0, fmt, args);
  YAO_WARN_POP
  va_end(args);
  YAO_CLAIM(res_num >= 0);

  std::size_t len = static_cast<std::size_t>(res_num) + 1u;
  std::vector<char> buf(len);

  va_start(args, fmt);
  YAO_WARN_PUSH
  YAO_WARN_OFF__FORMAT_NON_LITERAL
  [[maybe_unused]] int res = std::vsnprintf(buf.data(), len, fmt, args);
  YAO_WARN_POP
  va_end(args);
  YAO_CLAIM(res >= 0);

  os << buf.data();
}

} // namespace yao::prt
