#ifndef __YAO__DEF__ATTR__HPP__
#define __YAO__DEF__ATTR__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__COMPILER == YAO_CONFIG__COMPILER__MSVC

#define YAO_ATTR__EMPTY_BASES __declspec(empty_bases)

#else

#define YAO_ATTR__EMPTY_BASES

#endif

#endif
