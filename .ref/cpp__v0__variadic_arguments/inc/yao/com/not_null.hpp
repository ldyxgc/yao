#ifndef __YAO__COM__NOT_NULL__HPP__
#define __YAO__COM__NOT_NULL__HPP__

#include "yao/req/c_t_pointer.hpp"
#include "yao/req/c_t_std_shared_ptr.hpp"
#include "yao/req/c_t_std_unique_ptr.hpp"

namespace yao::com {

template <typename T>
  requires req::c_t_pointer<T> || req::c_t_std_unique_ptr<T> ||
               req::c_t_std_shared_ptr<T>
using not_null = T;

} // namespace yao::com

#endif
