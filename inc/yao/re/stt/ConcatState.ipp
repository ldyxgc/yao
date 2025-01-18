#ifndef __YAO__RE__STT__CONCAT_STATE__IPP__
#define __YAO__RE__STT__CONCAT_STATE__IPP__

#include "yao/re/stt/ConcatState.hpp"

#include <utility>

#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
template <typename _LhsState, typename _RhsState>
ConcatState<LhsState, RhsState>::ConcatState(_LhsState &&lhs_state,
                                             _RhsState &&rhs_state)
    : _lhs_state{std::forward<_LhsState>(lhs_state)},
      _raw_rhs_state{std::forward<_RhsState>(rhs_state)}, _rhs_state_set{},
      _is_final{_lhs_state.is_final() && _raw_rhs_state.is_final()} {}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
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
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::is_final() const {
  return _is_final;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::is_dead() const {
  return _lhs_state.is_dead() && _rhs_state_set.empty();
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
bool ConcatState<LhsState, RhsState>::cmp_less_in_state(
    const ConcatState &lhs, const ConcatState &rhs) {
  return lhs < rhs;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
typename ConcatState<LhsState, RhsState>::CmpLessInState
ConcatState<LhsState, RhsState>::get_cmp_less_in_state() const {
  return cmp_less_in_state;
}

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
void ConcatState<LhsState, RhsState>::print_type(
    std::ostream &os, const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "ConcatState";
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
void ConcatState<LhsState, RhsState>::print_value(
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
  os << "_raw_rhs_state:";
  prt::print_value(os, _raw_rhs_state, args, indent_level);
  os << '\n';
  prt::print_indent(os, indent_level);
  os << "_rhs_state_set:";
  prt::print_value(os, _rhs_state_set, args, indent_level);
  os << '\n';
  prt::print_indent(os, indent_level);
  os << "_is_final:";
  prt::print_value(os, _is_final, args, indent_level);
}

} // namespace yao::re::stt

#endif
