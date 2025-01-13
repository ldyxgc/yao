#ifndef __YAO__RE__STT__KLEENE_STATE__IPP__
#define __YAO__RE__STT__KLEENE_STATE__IPP__

#include "yao/re/stt/KleeneState.hpp"

#include <utility>

namespace yao::re::stt {

template <typename SubState, typename SubStateCmp>
  requires c_r_no_cvref_State<SubState>
KleeneState<SubState, SubStateCmp>::KleeneState(
    const SubState &sub_state, const SubStateCmp &sub_state_cmp)
    : _raw_sub_state{sub_state}, _sub_state_set{sub_state_cmp},
      _is_final{true} {}

template <typename SubState, typename SubStateCmp>
  requires c_r_no_cvref_State<SubState>
KleeneState<SubState, SubStateCmp>::KleeneState(
    SubState &&sub_state, const SubStateCmp &sub_state_cmp)
    : _raw_sub_state{std::move(sub_state)}, _sub_state_set{sub_state_cmp},
      _is_final{true} {}

template <typename SubState, typename SubStateCmp>
  requires c_r_no_cvref_State<SubState>
void KleeneState<SubState, SubStateCmp>::match(const Symbol &symbol) {
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

template <typename SubState, typename SubStateCmp>
  requires c_r_no_cvref_State<SubState>
bool KleeneState<SubState, SubStateCmp>::is_final() const {
  return _is_final;
}

template <typename SubState, typename SubStateCmp>
  requires c_r_no_cvref_State<SubState>
bool KleeneState<SubState, SubStateCmp>::is_dead() const {
  return _is_final == false && _sub_state_set.empty();
}

} // namespace yao::re::stt

#endif
