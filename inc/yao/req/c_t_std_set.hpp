#ifndef __YAO__REQ__C_T_STD_SET__HPP__
#define __YAO__REQ__C_T_STD_SET__HPP__

#include <concepts>
#include <set>

namespace yao::req {

// c: concept, t: type
template <typename T>
concept c_t_std_set =
    std::same_as<T, std::set<typename T::key_type, typename T::key_compare,
                             typename T::allocator_type>>;

} // namespace yao::req

#endif
