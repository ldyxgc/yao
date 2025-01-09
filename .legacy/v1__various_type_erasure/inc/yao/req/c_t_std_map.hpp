#ifndef __YAO__REQ__C_T_STD_MAP__HPP__
#define __YAO__REQ__C_T_STD_MAP__HPP__

#include <concepts>
#include <map>

namespace yao::req {

// c: concept, t: type
template <typename T>
concept c_t_std_map =
    std::same_as<T,
                 std::map<typename T::key_type, typename T::mapped_type,
                          typename T::key_compare, typename T::allocator_type>>;

} // namespace yao::req

#endif
