#ifndef __YAO__RE__STT__CONCAT_STATE__IPP__
#define __YAO__RE__STT__CONCAT_STATE__IPP__

#include "yao/re/stt/ConcatState.hpp"

#include <utility>

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires impl::c_r_ConcatState<LhsState, RhsState>
template <typename _LhsState, typename _RhsState>
  requires c_r_State_with_same_Symbol<std::remove_cvref_t<_LhsState>,
                                      std::remove_cvref_t<_RhsState>>
ConcatState<LhsState, RhsState>::ConcatState(_LhsState &&lhs_state,
                                             _RhsState &&rhs_state)
    : _lhs_state{std::forward<_LhsState>(lhs_state)},
      _raw_rhs_state{std::forward<_RhsState>(rhs_state)}, _rhs_state_set{},
      _is_final{_lhs_state.is_final() && _raw_rhs_state.is_final()} {}

template <typename LhsState, typename RhsState>
  requires impl::c_r_ConcatState<LhsState, RhsState>
void ConcatState<LhsState, RhsState>::match(const Symbol &symbol) {
  std::set<RhsState> new_rhs_state_set;
  _is_final = false;
  if (_lhs_state.is_final()) {
    auto new_rhs_state = _raw_rhs_state;
    new_rhs_state.match(symbol);
    _is_final = new_rhs_state.is_final();
    if (new_rhs_state.is_dead() == false)
      new_rhs_state_set.insert(std::move(new_rhs_state));
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
  requires impl::c_r_ConcatState<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::is_final() const {
  return _is_final;
}

template <typename LhsState, typename RhsState>
  requires impl::c_r_ConcatState<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state_set.empty();
}

} // namespace yao::re::stt

#endif
