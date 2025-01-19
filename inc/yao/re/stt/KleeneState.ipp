#ifndef __YAO__RE__STT__KLEENE_STATE__IPP__
#define __YAO__RE__STT__KLEENE_STATE__IPP__

#include "yao/re/stt/KleeneState.hpp"

#include <utility>

#include "yao/def/claim.hpp"
#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
KleeneState<SubState>::KleeneState(const SubState &sub_state)
    : _raw_sub_state{sub_state},
      _sub_state_set{_raw_sub_state.get_cmp_less_in_state()}, _is_final{true} {}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
KleeneState<SubState>::KleeneState(SubState &&sub_state)
    : _raw_sub_state{std::move(sub_state)},
      _sub_state_set{_raw_sub_state.get_cmp_less_in_state()}, _is_final{true} {}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
void KleeneState<SubState>::match(const Symbol &symbol) {
  decltype(_sub_state_set) new_sub_state_set{_sub_state_set.key_comp()};
  if (_is_final) {
    auto new_sub_state = _raw_sub_state;
    new_sub_state.match(symbol);
    _is_final = new_sub_state.is_final();
    if (new_sub_state.is_dead() == false)
      new_sub_state_set.insert(std::move(new_sub_state));
  }
  while (_sub_state_set.empty() == false) {
    auto node = _sub_state_set.extract(_sub_state_set.begin());
    auto &sub_state = node.value();
    sub_state.match(symbol);
    if (sub_state.is_final())
      _is_final = true;
    if (sub_state.is_dead() == false)
      new_sub_state_set.insert(std::move(node));
  }
  _sub_state_set = std::move(new_sub_state_set);
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
bool KleeneState<SubState>::is_final() const {
  return _is_final;
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
bool KleeneState<SubState>::is_dead() const {
  return _is_final == false && _sub_state_set.empty();
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
std::strong_ordering
KleeneState<SubState>::cmp_order_in_state(const KleeneState &lhs,
                                          const KleeneState &rhs) {
  // YAO_CLAIM(lhs._raw_sub_state.get_cmp_order_in_state()(lhs._raw_sub_state,
  //                                                       rhs._raw_sub_state)
  //                                                       ==
  //           std::strong_ordering::equal);
  // if (auto res = lhs._raw_sub_state.get_cmp_order_in_state()(
  //         lhs._raw_sub_state, rhs._raw_sub_state);
  //     res != std::strong_ordering::equal)
  //   return res;

  if (auto res = lhs._sub_state_set <=> rhs._sub_state_set;
      res != std::strong_ordering::equal)
    return res;

  return lhs._is_final <=> rhs._is_final;
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
typename KleeneState<SubState>::CmpOrderInState
KleeneState<SubState>::get_cmp_order_in_state() const {
  return cmp_order_in_state;
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
bool KleeneState<SubState>::cmp_less_in_state(const KleeneState &lhs,
                                              const KleeneState &rhs) {
  return cmp_order_in_state(lhs, rhs) == std::strong_ordering::less;
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
typename KleeneState<SubState>::CmpLessInState
KleeneState<SubState>::get_cmp_less_in_state() const {
  return cmp_less_in_state;
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
void KleeneState<SubState>::print_type(std::ostream &os,
                                       const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "KleeneState";
  if (args.tmpl_args) {
    os << '<';
    prt::print_type<SubState>(os, args);
    os << '>';
  }
}

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
void KleeneState<SubState>::print_value(std::ostream &os,
                                        const prt::PrintValueArgs &args,
                                        uint indent_level) const {
  print_type(os, args.print_type_args);
  os << ":\n";
  ++indent_level;
  prt::print_indent(os, indent_level);
  os << "_raw_sub_state:";
  prt::print_value(os, _raw_sub_state, args, indent_level);
  os << '\n';
  prt::print_indent(os, indent_level);
  os << "_sub_state_set:";
  prt::print_value(os, _sub_state_set, args, indent_level);
  os << '\n';
  prt::print_indent(os, indent_level);
  os << "_is_final:";
  prt::print_value(os, _is_final, args, indent_level);
}

} // namespace yao::re::stt

#endif
