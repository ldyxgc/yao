#ifndef __YAO__DEF__CHECK__HPP__
#define __YAO__DEF__CHECK__HPP__

#include <cstdlib>
#include <iostream>

#define YAO_CHECK(expr)                                                        \
  ((expr) ? void(0)                                                            \
          : (std::cerr << __FILE__ << ':' << __LINE__ << ": Check `" << #expr  \
                       << "` failed\n",                                        \
             std::exit(EXIT_FAILURE)))

#endif
