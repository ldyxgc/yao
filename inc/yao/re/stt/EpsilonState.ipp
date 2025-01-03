#ifndef __YAO__RE__STT__EPSILON_STATE__IPP__
#define __YAO__RE__STT__EPSILON_STATE__IPP__

#include "yao/re/stt/EpsilonState.hpp"

#include "yao/def/claim.hpp"
#include "yao/prt/print_type.hpp"

namespace yao::re::stt {

namespace impl {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, EpsilonStateBase::Label>
void EpsilonStateBase::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::impl::EpsilonStateBase::";
  os << "Label";
}

template <bool ns, bool tp>
void EpsilonStateBase::print_value(std::ostream &os, Label label) {
  print_type<Label, ns, tp>(os);
  os << ": ";
  switch (label) {
  case Label::FINAL:
    os << "FINAL";
    break;
  case Label::DEAD:
    os << "DEAD";
    break;
  default:
    YAO_CLAIM(false);
    break;
  }
}

} // namespace impl

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
EpsilonState<_Symbol>::EpsilonState() : _label(Label::FINAL) {}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
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
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
bool EpsilonState<_Symbol>::is_final() const {
  return _label == Label::FINAL;
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
bool EpsilonState<_Symbol>::is_dead() const {
  return _label == Label::DEAD;
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void EpsilonState<_Symbol>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "EpsilonState";
  if constexpr (tp) {
    os << '<';
    prt::print_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void EpsilonState<_Symbol>::print_value(std::ostream &os) const {
  print_type<ns, tp>(os);
  os << ": {_label:";
  EpsilonStateBase::print_value<ns, tp>(os, _label);
  os << '}';
}

} // namespace yao::re::stt

#endif
