#ifndef __YAO__LAB__RE__STT__C_R_STATE_WITH_SAME_SYMBOL__HPP__
#define __YAO__LAB__RE__STT__C_R_STATE_WITH_SAME_SYMBOL__HPP__

#include <concepts>

#include "yao/lab/re/stt/c_o_State.hpp"

namespace yao::lab::re::stt {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_State_with_same_Symbol =
    c_o_State<LhsState> && c_o_State<RhsState> &&
    std::same_as<typename LhsState::Symbol, typename RhsState::Symbol>;

} // namespace yao::lab::re::stt

#endif
