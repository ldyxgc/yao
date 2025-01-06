#ifndef __YAO__COM__OWNER__HPP__
#define __YAO__COM__OWNER__HPP__

#include "yao/req/c_t_pointer.hpp"

namespace yao::com {

template <typename T>
  requires req::c_t_pointer<T>
using owner = T;

} // namespace yao::com

#endif
