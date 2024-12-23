#include "yao/prt/osprintf.hpp"

#include <cstdarg>
#include <cstdio>
#include <vector>

namespace yao::prt {

void osprintf(std::ostream &os, const char *fmt, ...) {
  std::va_list args;
  va_start(args, fmt);
  std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, fmt, args));
  va_end(args);
  va_start(args, fmt);
  std::vsnprintf(buf.data(), buf.size(), fmt, args);
  va_end(args);
  os << buf.data();
}

} // namespace yao::prt
