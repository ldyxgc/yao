#ifndef __YAO__DEF__WARN__HPP__
#define __YAO__DEF__WARN__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__COMPILER == YAO_CONFIG__COMPILER__GNU

#define YAO_WARN_PUSH _Pragma("GCC diagnostic push")
#define YAO_WARN_POP _Pragma("GCC diagnostic pop")

#define YAO_WARN_OFF__DEPRECATED_DECLARATION                                   \
  _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#define YAO_WARN_OFF__FORMAT_NON_LITERAL                                       \
  _Pragma("GCC diagnostic ignored \"-Wformat-nonliteral\"")
#define YAO_WARN_OFF__PADDING _Pragma("GCC diagnostic ignored \"-Wpadded\"")
#define YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT

#elif YAO_CONFIG__COMPILER == YAO_CONFIG__COMPILER__CLANG

#define YAO_WARN_PUSH _Pragma("clang diagnostic push")
#define YAO_WARN_POP _Pragma("clang diagnostic pop")

#define YAO_WARN_OFF__DEPRECATED_DECLARATION                                   \
  _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#define YAO_WARN_OFF__FORMAT_NON_LITERAL                                       \
  _Pragma("clang diagnostic ignored \"-Wformat-nonliteral\"")
#define YAO_WARN_OFF__PADDING _Pragma("clang diagnostic ignored \"-Wpadded\"")
#define YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT                            \
  _Pragma("clang diagnostic ignored \"-Wzero-as-null-pointer-constant\"")

#elif YAO_CONFIG__COMPILER == YAO_CONFIG__COMPILER__MSVC

#define YAO_WARN_PUSH _Pragma("warning(push)")
#define YAO_WARN_POP _Pragma("warning(pop)")

#define YAO_WARN_OFF__DEPRECATED_DECLARATION _Pragma("warning(disable:4996)")
#define YAO_WARN_OFF__FORMAT_NON_LITERAL _Pragma("warning(disable:4774)")
#define YAO_WARN_OFF__PADDING _Pragma("warning(disable:4820)")
#define YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT

#endif

#endif
