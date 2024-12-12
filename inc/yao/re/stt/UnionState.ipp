#ifndef __YAO__RE__STT__UNION_STATE__IPP__
#define __YAO__RE__STT__UNION_STATE__IPP__

#include "yao/re/stt/UnionState.hpp"

#include "yao/prt/osprint_type.hpp"
#include "yao/prt/osprint_value.hpp"

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
UnionState<LhsState, RhsState>::UnionState(const LhsState &lhs_state,
                                           const RhsState &rhs_state)
    : _lhs_state{lhs_state}, _rhs_state{rhs_state} {}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
StateType UnionState<LhsState, RhsState>::type() const {
  return StateType::UnionState;
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
void UnionState<LhsState, RhsState>::match(const Symbol &symbol) {
  _lhs_state.match(symbol);
  _rhs_state.match(symbol);
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_final() const {
  return _lhs_state.is_final() || _rhs_state.is_final();
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state.is_dead();
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
template <bool ns, bool tp>
void UnionState<LhsState, RhsState>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "UnionState";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<LhsState, ns, tp>(os);
    os << '|';
    prt::osprint_type<RhsState, ns, tp>(os);
    os << '>';
  }
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
template <bool ns, bool tp>
void UnionState<LhsState, RhsState>::osprint_value(std::ostream &os) const {
  prt::osprint_type<UnionState, ns, tp>(os);
  os << ": {_lhs_state:";
  prt::osprint_value<ns, tp>(os, _lhs_state);
  os << ",_rhs_state:";
  prt::osprint_value<ns, tp>(os, _rhs_state);
  os << '}';
}

} // namespace yao::re::stt

#endif
