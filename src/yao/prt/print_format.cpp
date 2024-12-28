#include "yao/prt/print_format.hpp"

#include <cstdarg>
#include <cstdio>
#include <vector>

#include "yao/def/claim.hpp"

namespace yao::prt {

void print_format(std::ostream &os, not_null<czstring> fmt, ...) {
  YAO_CLAIM(fmt != nullptr);
  std::va_list args;

  va_start(args, fmt);
  int res_num = std::vsnprintf(nullptr, 0, fmt, args);
  va_end(args);
  YAO_CLAIM(res_num >= 0);

  std::size_t len = static_cast<std::size_t>(res_num) + 1u;
  std::vector<char> buf(len);

  va_start(args, fmt);
  int res = std::vsnprintf(buf.data(), len, fmt, args);
  va_end(args);
  YAO_CLAIM(res >= 0);

  os << buf.data();
}

} // namespace yao::prt
