#ifndef __YAO__RE__STT__EPSILON_STATE__IPP__
#define __YAO__RE__STT__EPSILON_STATE__IPP__

#include "yao/re/stt/EpsilonState.hpp"

#include "yao/def/claim.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
EpsilonState<_Symbol>::EpsilonState() : _label(Label::FINAL) {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void EpsilonState<_Symbol>::match(const Symbol &) {
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

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool EpsilonState<_Symbol>::is_final() const {
  return _label == Label::FINAL;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool EpsilonState<_Symbol>::is_dead() const {
  return _label == Label::DEAD;
}

} // namespace yao::re::stt

#endif
