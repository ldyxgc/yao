#ifndef __YAO__REQ__C_T_POINTER__HPP__
#define __YAO__REQ__C_T_POINTER__HPP__

#include <type_traits>

namespace yao::req {

namespace impl {

template <class T> struct c_t_pointer : std::false_type {};
template <class T> struct c_t_pointer<T *> : std::true_type {};

} // namespace impl

// c: concept, t: type
template <typename T>
concept c_t_pointer = impl::c_t_pointer<T>::value;

} // namespace yao::req

#endif
