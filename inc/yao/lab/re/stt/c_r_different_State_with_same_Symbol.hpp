#ifndef __YAO__LAB__RE__STT__C_R_DIFFERENT_STATE_WITH_SAME_SYMBOL__HPP__
#define __YAO__LAB__RE__STT__C_R_DIFFERENT_STATE_WITH_SAME_SYMBOL__HPP__

#include <concepts>

#include "yao/lab/re/stt/c_r_State_with_same_Symbol.hpp"

namespace yao::lab::re::stt {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_different_State_with_same_Symbol =
    c_r_State_with_same_Symbol<LhsState, RhsState> &&
    (!std::same_as<LhsState, RhsState>);

} // namespace yao::lab::re::stt

#endif
