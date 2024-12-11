#ifndef __YAO__RE__STT__STATE_BASE__IPP__
#define __YAO__RE__STT__STATE_BASE__IPP__

#include "yao/re/stt/StateBase.hpp"

#include <concepts>

#include "yao/prt/c_mf_osprint_value.hpp"
#include "yao/prt/c_smf_osprint_type.hpp"
#include "yao/re/c_t_Symbol.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, o: object
template <typename State, typename Symbol = typename State::Symbol>
concept c_o_State =
    c_t_Symbol<Symbol> && //
    std::totally_ordered<State> && std::three_way_comparable<State> &&
    requires {
      static_cast<void (State::*)(const Symbol &symbol)>(&State::match);
      static_cast<bool (State::*)() const>(&State::is_final);
      static_cast<bool (State::*)() const>(&State::is_dead);
    } && //
    prt::c_smf_osprint_type<State> && prt::c_mf_osprint_value<State>;

} // namespace impl

template <typename State> StateBase<State>::StateBase() {
  static_assert(impl::c_o_State<State>);
}

} // namespace yao::re::stt

#endif
