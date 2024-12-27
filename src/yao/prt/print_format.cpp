#include "yao/prt/print_format.hpp"

#include <cstdarg>
#include <cstdio>
#include <vector>

#include "yao/def/claim.hpp"

namespace yao::prt {

void print_format(std::ostream &os, const char *fmt, ...) {
  YAO_CLAIM(fmt != nullptr);
  std::va_list args;

  va_start(args, fmt);
  int res_num = std::vsnprintf(nullptr, 0, fmt, args);
  va_end(args);
  YAO_CLAIM(res_num >= 0);

  std::vector<char> buf(1 + res_num);

  va_start(args, fmt);
  int res = std::vsnprintf(buf.data(), buf.size(), fmt, args);
  va_end(args);
  YAO_CLAIM(res >= 0);

  os << buf.data();
}

} // namespace yao::prt
