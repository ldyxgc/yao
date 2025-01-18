#ifndef __YAO__RE__STT__C_R_NO_CVREF_DIFFERENT_STATE_WITH_SAME_SYMBOL__HPP__
#define __YAO__RE__STT__C_R_NO_CVREF_DIFFERENT_STATE_WITH_SAME_SYMBOL__HPP__

#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_no_cvref_different_State_with_same_Symbol =
    req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
    c_r_different_State_with_same_Symbol<LhsState, RhsState>;

} // namespace yao::re::stt

#endif
