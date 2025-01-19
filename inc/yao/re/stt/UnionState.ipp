#ifndef __YAO__RE__STT__UNION_STATE__IPP__
#define __YAO__RE__STT__UNION_STATE__IPP__

#include "yao/re/stt/UnionState.hpp"

#include <utility>

#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
template <typename _LhsState, typename _RhsState>
UnionState<LhsState, RhsState>::UnionState(_LhsState &&lhs_state,
                                           _RhsState &&rhs_state)
    : _lhs_state{std::forward<_LhsState>(lhs_state)},
      _rhs_state{std::forward<_RhsState>(rhs_state)} {}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
void UnionState<LhsState, RhsState>::match(const Symbol &symbol) {
  _lhs_state.match(symbol);
  _rhs_state.match(symbol);
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_final() const {
  return _lhs_state.is_final() || _rhs_state.is_final();
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state.is_dead();
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
std::strong_ordering
UnionState<LhsState, RhsState>::cmp_order_in_state(const UnionState &lhs,
                                                   const UnionState &rhs) {
  return lhs <=> rhs;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
typename UnionState<LhsState, RhsState>::CmpOrderInState
UnionState<LhsState, RhsState>::get_cmp_order_in_state() const {
  return cmp_order_in_state;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
bool UnionState<LhsState, RhsState>::cmp_less_in_state(const UnionState &lhs,
                                                       const UnionState &rhs) {
  return lhs < rhs;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
typename UnionState<LhsState, RhsState>::CmpLessInState
UnionState<LhsState, RhsState>::get_cmp_less_in_state() const {
  return cmp_less_in_state;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
void UnionState<LhsState, RhsState>::print_type(
    std::ostream &os, const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "UnionState";
  if (args.tmpl_args) {
    os << '<';
    prt::print_type<LhsState>(os, args);
    os << ',';
    prt::print_type<RhsState>(os, args);
    os << '>';
  }
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
void UnionState<LhsState, RhsState>::print_value(
    std::ostream &os, const prt::PrintValueArgs &args,
    uint indent_level) const {
  print_type(os, args.print_type_args);
  os << ":\n";
  ++indent_level;
  prt::print_indent(os, indent_level);
  os << "_lhs_state:";
  prt::print_value(os, _lhs_state, args, indent_level);
  os << '\n';
  prt::print_indent(os, indent_level);
  os << "_rhs_state:";
  prt::print_value(os, _rhs_state, args, indent_level);
}

} // namespace yao::re::stt

#endif
