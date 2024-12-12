#ifndef __YAO__DEF__CHECK__HPP__
#define __YAO__DEF__CHECK__HPP__

#include <cstdlib>
#include <iostream>

#include "yao/prt/impl/func/osprintf.hpp"

#define YAO_CHECK(...)                                                         \
  ((__VA_ARGS__) ? void(0)                                                     \
                 : (yao::prt::impl::func::osprintf(                            \
                        std::cerr, "%s:%i: Check `%s` failed\n", __FILE__,     \
                        __LINE__, #__VA_ARGS__),                               \
                    std::exit(EXIT_FAILURE)))

#endif
