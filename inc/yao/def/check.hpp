#ifndef __YAO__DEF__CHECK__HPP__
#define __YAO__DEF__CHECK__HPP__

#include <cstdlib>
#include <iostream>

#define YAO_CHECK(...)                                                         \
  ((__VA_ARGS__) ? void(0)                                                     \
                 : (std::cerr << __FILE__ << ':' << __LINE__ << ": Check `"    \
                              << #__VA_ARGS__ << "` failed\n",                 \
                    std::exit(EXIT_FAILURE)))

#endif
