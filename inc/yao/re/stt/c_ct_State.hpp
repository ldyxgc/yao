#ifndef __YAO__RE__STT__C_CT_STATE__HPP__
#define __YAO__RE__STT__C_CT_STATE__HPP__

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, ct: conceptual type
template <typename State, typename Symbol = typename State::Symbol>
concept c_ct_State =
    req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol> && //
    requires {
      static_cast<void (State::*)(const Symbol &symbol)>(&State::match);
      static_cast<bool (State::*)() const>(&State::is_final);
      static_cast<bool (State::*)() const>(&State::is_dead);
    };

} // namespace impl

// c: concept, ct: conceptual type
template <typename State>
concept c_ct_State = impl::c_ct_State<State>;

} // namespace yao::re::stt

#endif
