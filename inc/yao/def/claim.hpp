#ifndef __YAO__DEF__CLAIM__HPP__
#define __YAO__DEF__CLAIM__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__BUILD_TYPE == YAO_CONFIG__BUILD_TYPE__DEBUG

#include <cstdlib>
#include <iostream>

#if YAO_CONFIG__COMPILER == YAO_CONFIG__COMPILER__MSVC

#define YAO_CLAIM(...)                                                         \
  ((__VA_ARGS__) ? void(0)                                                     \
                 : (std::cerr << __FILE__ << ':' << __LINE__ << ": Claim `"    \
                              << #__VA_ARGS__ << "` failed\n",                 \
                    _set_abort_behavior(0, _WRITE_ABORT_MSG), std::abort()))

#else

#define YAO_CLAIM(...)                                                         \
  ((__VA_ARGS__) ? void(0)                                                     \
                 : (std::cerr << __FILE__ << ':' << __LINE__ << ": Claim `"    \
                              << #__VA_ARGS__ << "` failed\n",                 \
                    std::abort()))

#endif

#elif YAO_CONFIG__BUILD_TYPE == YAO_CONFIG__BUILD_TYPE__RELEASE

#define YAO_CLAIM(...) void(0)

#endif

#endif
