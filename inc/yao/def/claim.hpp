#ifndef __YAO__DEF__CLAIM__HPP__
#define __YAO__DEF__CLAIM__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__BUILD_TYPE == YAO_CONFIG__BUILD_TYPE__DEBUG

#include <cstdlib>
#include <iostream>

#include "yao/prt/osprintf.hpp"

#define YAO_CLAIM(expr)                                                        \
  ((expr) ? void(0)                                                            \
          : (yao::prt::osprintf(std::cerr, "%s:%i: Claim `%s` failed\n",       \
                                __FILE__, __LINE__, #expr),                    \
             std::abort()))

#elif YAO_CONFIG__BUILD_TYPE == YAO_CONFIG__BUILD_TYPE__RELEASE

#define YAO_CLAIM(expr) void(0)

#endif

#endif
