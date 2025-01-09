#ifndef __YAO__RE__STT__C_R_STATE_WITH_SAME_SYMBOL__HPP__
#define __YAO__RE__STT__C_R_STATE_WITH_SAME_SYMBOL__HPP__

#include <concepts>

#include "yao/re/stt/c_ct_State.hpp"

namespace yao::re::stt {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_State_with_same_Symbol =
    c_ct_State<LhsState> && c_ct_State<RhsState> &&
    std::same_as<typename LhsState::Symbol, typename RhsState::Symbol>;

} // namespace yao::re::stt

#endif
