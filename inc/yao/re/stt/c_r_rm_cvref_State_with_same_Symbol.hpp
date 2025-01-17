#ifndef __YAO__RE__STT__C_R_RM_CVREF_STATE_WITH_SAME_SYMBOL__HPP__
#define __YAO__RE__STT__C_R_RM_CVREF_STATE_WITH_SAME_SYMBOL__HPP__

#include <type_traits>

#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"

namespace yao::re::stt {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_rm_cvref_State_with_same_Symbol =
    c_r_State_with_same_Symbol<std::remove_cvref_t<LhsState>,
                               std::remove_cvref_t<RhsState>>;

} // namespace yao::re::stt

#endif
