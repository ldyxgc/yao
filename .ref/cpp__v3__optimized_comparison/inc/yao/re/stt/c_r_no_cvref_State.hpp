#ifndef __YAO__RE__STT__C_R_NO_CVREF_STATE__HPP__
#define __YAO__RE__STT__C_R_NO_CVREF_STATE__HPP__

#include "yao/re/stt/c_ct_State.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

// c: concept, r: require
template <typename State>
concept c_r_no_cvref_State = req::c_r_no_cvref<State> && c_ct_State<State>;

} // namespace yao::re::stt

#endif
