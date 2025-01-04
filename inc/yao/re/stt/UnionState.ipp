#ifndef __YAO__RE__STT__UNION_STATE__IPP__
#define __YAO__RE__STT__UNION_STATE__IPP__

#include "yao/re/stt/UnionState.hpp"

#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
               c_r_State_with_same_Symbol<LhsState, RhsState>
UnionState<LhsState, RhsState>::UnionState(const LhsState &lhs_state,
                                           const RhsState &rhs_state)
    : _lhs_state{lhs_state}, _rhs_state{rhs_state} {}

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
           c_r_State_with_same_Symbol<LhsState, RhsState>
void UnionState<LhsState, RhsState>::match(const Symbol &symbol) {
  _lhs_state.match(symbol);
  _rhs_state.match(symbol);
}

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
           c_r_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_final() const {
  return _lhs_state.is_final() || _rhs_state.is_final();
}

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
           c_r_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state.is_dead();
}

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
           c_r_State_with_same_Symbol<LhsState, RhsState>
template <bool ns, bool tp>
void UnionState<LhsState, RhsState>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "UnionState";
  if constexpr (tp) {
    os << '<';
    prt::print_type<LhsState, ns, tp>(os);
    os << '|';
    prt::print_type<RhsState, ns, tp>(os);
    os << '>';
  }
}

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
           c_r_State_with_same_Symbol<LhsState, RhsState>
template <bool ns, bool tp>
void UnionState<LhsState, RhsState>::print_value(std::ostream &os) const {
  print_type<ns, tp>(os);
  os << ": {_lhs_state:";
  prt::print_value<ns, tp>(os, _lhs_state);
  os << ",_rhs_state:";
  prt::print_value<ns, tp>(os, _rhs_state);
  os << '}';
}

} // namespace yao::re::stt

#endif
