#ifndef __YAO__RE__STT__KLEENE_STATE__IPP__
#define __YAO__RE__STT__KLEENE_STATE__IPP__

#include "yao/re/stt/KleeneState.hpp"

#include <utility>

#include "yao/prt/osprint_type.hpp"
#include "yao/prt/osprint_value.hpp"

namespace yao::re::stt {

template <typename SubState>
  requires c_o_State<SubState>
KleeneState<SubState>::KleeneState(const SubState &sub_state)
    : _raw_sub_state{sub_state}, _sub_state_set{}, _is_final{true} {}

template <typename SubState>
  requires c_o_State<SubState>
void KleeneState<SubState>::match(const Symbol &symbol) {
  std::set<SubState> new_sub_state_set;
  if (_is_final) {
    auto sub_state = _raw_sub_state;
    sub_state.match(symbol);
    _is_final = sub_state.is_final();
    if (sub_state.is_dead() == false)
      new_sub_state_set.insert(sub_state);
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
  requires c_o_State<SubState>
bool KleeneState<SubState>::is_final() const {
  return _is_final;
}

template <typename SubState>
  requires c_o_State<SubState>
bool KleeneState<SubState>::is_dead() const {
  return _is_final == false && _sub_state_set.empty();
}

template <typename SubState>
  requires c_o_State<SubState>
template <bool ns, bool tp>
void KleeneState<SubState>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "KleeneState";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<SubState, ns, tp>(os);
    os << '>';
  }
}

template <typename SubState>
  requires c_o_State<SubState>
template <bool ns, bool tp>
void KleeneState<SubState>::osprint_value(std::ostream &os) const {
  prt::osprint_type<KleeneState, ns, tp>(os);
  os << ": {_raw_sub_state:";
  prt::osprint_value<ns, tp>(os, _raw_sub_state);
  os << ",_sub_state_set:";
  prt::osprint_value<ns, tp>(os, _sub_state_set);
  os << ",_is_final:";
  prt::osprint_value<ns, tp>(os, _is_final);
  os << '}';
}

} // namespace yao::re::stt

#endif
