#ifndef __YAO__DEF__CHECK__HPP__
#define __YAO__DEF__CHECK__HPP__

#include <cstdlib>
#include <iostream>

#include "yao/prt/osprintf.hpp"

#define YAO_CHECK(expr)                                                        \
  ((expr) ? void(0)                                                            \
          : (yao::prt::osprintf(std::cerr, "%s:%i: Check `%s` failed\n",       \
                                __FILE__, __LINE__, #expr),                    \
             std::exit(EXIT_FAILURE)))

#endif
