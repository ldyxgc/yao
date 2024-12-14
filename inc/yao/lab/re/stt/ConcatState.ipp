#ifndef __YAO__LAB__RE__STT__CONCAT_STATE__IPP__
#define __YAO__LAB__RE__STT__CONCAT_STATE__IPP__

#include "yao/lab/re/stt/ConcatState.hpp"

#include <utility>

#include "yao/lab/prt/osprint_type.hpp"
#include "yao/lab/prt/osprint_value.hpp"

namespace yao::lab::re::stt {

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
ConcatState<LhsState, RhsState>::ConcatState(const LhsState &lhs_state,
                                             const RhsState &rhs_state)
    : _lhs_state{lhs_state}, _raw_rhs_state{rhs_state}, _rhs_state_set{},
      _is_final{_lhs_state.is_final() && _raw_rhs_state.is_final()} {}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
StateType ConcatState<LhsState, RhsState>::type() const {
  return StateType::ConcatState;
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
void ConcatState<LhsState, RhsState>::match(const Symbol &symbol) {
  std::set<RhsState> new_rhs_state_set;
  _is_final = false;
  if (_lhs_state.is_final()) {
    auto rhs_state = _raw_rhs_state;
    rhs_state.match(symbol);
    _is_final = rhs_state.is_final();
    if (rhs_state.is_dead() == false)
      new_rhs_state_set.insert(rhs_state);
  }
  _lhs_state.match(symbol);
  if (_lhs_state.is_final() && _raw_rhs_state.is_final())
    _is_final = true;
  while (_rhs_state_set.empty() == false) {
    auto node = _rhs_state_set.extract(_rhs_state_set.begin());
    auto &rhs_state = node.value();
    rhs_state.match(symbol);
    if (rhs_state.is_final())
      _is_final = true;
    if (rhs_state.is_dead() == false)
      new_rhs_state_set.insert(std::move(node));
  }
  _rhs_state_set = std::move(new_rhs_state_set);
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::is_final() const {
  return _is_final;
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state_set.empty();
}

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
template <bool ns, bool tp>
void ConcatState<LhsState, RhsState>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::lab::re::stt::";
  os << "ConcatState";
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
void ConcatState<LhsState, RhsState>::osprint_value(std::ostream &os) const {
  prt::osprint_type<ConcatState, ns, tp>(os);
  os << ": {_lhs_state:";
  prt::osprint_value<ns, tp>(os, _lhs_state);
  os << ",_raw_rhs_state:";
  prt::osprint_value<ns, tp>(os, _raw_rhs_state);
  os << ",_rhs_state_set:";
  prt::osprint_value<ns, tp>(os, _rhs_state_set);
  os << ",_is_final:";
  prt::osprint_value<ns, tp>(os, _is_final);
  os << '}';
}

} // namespace yao::lab::re::stt

#endif
