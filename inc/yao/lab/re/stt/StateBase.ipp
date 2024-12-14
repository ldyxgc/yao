#ifndef __YAO__LAB__RE__STT__STATE_BASE__IPP__
#define __YAO__LAB__RE__STT__STATE_BASE__IPP__

#include "yao/lab/re/stt/StateBase.hpp"

#include <concepts>

#include "yao/lab/prt/c_mf_osprint_value.hpp"
#include "yao/lab/prt/c_smf_osprint_type.hpp"
#include "yao/lab/re/c_t_Symbol.hpp"
#include "yao/lab/re/stt/StateType.hpp"

namespace yao::lab::re::stt {

namespace impl {

// c: concept, o: object
template <typename State, typename Symbol = typename State::Symbol>
concept c_o_State =
    c_t_Symbol<Symbol> && //
    std::totally_ordered<State> && std::three_way_comparable<State> &&
    requires {
      static_cast<StateType (State::*)() const>(&State::type);
      static_cast<void (State::*)(const Symbol &symbol)>(&State::match);
      static_cast<bool (State::*)() const>(&State::is_final);
      static_cast<bool (State::*)() const>(&State::is_dead);
    } && //
    prt::c_smf_osprint_type<State> && prt::c_mf_osprint_value<State>;

} // namespace impl

template <typename State> StateBase<State>::StateBase() {
  static_assert(impl::c_o_State<State>);
}

} // namespace yao::lab::re::stt

#endif
