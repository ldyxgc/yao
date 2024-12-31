#ifndef __YAO__REQ__C_R_NO_CVREF__HPP__
#define __YAO__REQ__C_R_NO_CVREF__HPP__

#include <concepts>
#include <type_traits>

namespace yao::req {

// c: concept, r: requirement
template <typename T>
concept c_r_no_cvref = std::same_as<T, std::remove_cvref_t<T>>;

} // namespace yao::req

#endif
