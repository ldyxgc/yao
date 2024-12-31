#ifndef __YAO__RE__STT__EPSILON_STATE__IPP__
#define __YAO__RE__STT__EPSILON_STATE__IPP__

#include "yao/re/stt/EpsilonState.hpp"

#include "yao/def/claim.hpp"

namespace yao::re::stt {

template <typename Symbol>
  requires req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol>
EpsilonState<Symbol>::EpsilonState() : _label(Label::FINAL) {}

template <typename Symbol>
  requires req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol>
void EpsilonState<Symbol>::match(const Symbol &) {
  switch (_label) {
  case Label::FINAL:
    _label = Label::DEAD;
    break;
  case Label::DEAD:
    break;
  default:
    YAO_CLAIM(false);
    break;
  }
}

template <typename Symbol>
  requires req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol>
bool EpsilonState<Symbol>::is_final() const {
  return _label == Label::FINAL;
}

template <typename Symbol>
  requires req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol>
bool EpsilonState<Symbol>::is_dead() const {
  return _label == Label::DEAD;
}

} // namespace yao::re::stt

#endif
