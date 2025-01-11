#ifndef __YAO__RE__STT__UNION_STATE__IPP__
#define __YAO__RE__STT__UNION_STATE__IPP__

#include "yao/re/stt/UnionState.hpp"

#include <utility>

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires impl::c_r_UnionState<LhsState, RhsState>
template <typename _LhsState, typename _RhsState>
  requires c_r_State_with_same_Symbol<std::remove_cvref_t<_LhsState>,
                                      std::remove_cvref_t<_RhsState>>
UnionState<LhsState, RhsState>::UnionState(_LhsState &&lhs_state,
                                           _RhsState &&rhs_state)
    : _lhs_state{std::forward<_LhsState>(lhs_state)},
      _rhs_state{std::forward<_RhsState>(rhs_state)} {}

template <typename LhsState, typename RhsState>
  requires impl::c_r_UnionState<LhsState, RhsState>
void UnionState<LhsState, RhsState>::match(const Symbol &symbol) {
  _lhs_state.match(symbol);
  _rhs_state.match(symbol);
}

template <typename LhsState, typename RhsState>
  requires impl::c_r_UnionState<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_final() const {
  return _lhs_state.is_final() || _rhs_state.is_final();
}

template <typename LhsState, typename RhsState>
  requires impl::c_r_UnionState<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state.is_dead();
}

} // namespace yao::re::stt

#endif
