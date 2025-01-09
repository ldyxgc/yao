#ifndef __YAO__REQ__C_T_STD_SHARED_PTR__HPP__
#define __YAO__REQ__C_T_STD_SHARED_PTR__HPP__

#include <concepts>
#include <memory>

namespace yao::req {

// c: concept, t: type
template <typename T>
concept c_t_std_shared_ptr =
    std::same_as<T, std::shared_ptr<typename T::element_type>>;

} // namespace yao::req

#endif
