#ifndef __YAO__RE__STT__EPSILON_STATE__IPP__
#define __YAO__RE__STT__EPSILON_STATE__IPP__

#include "yao/re/stt/EpsilonState.hpp"

#include "yao/def/claim.hpp"
#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"

namespace yao::re::stt {

namespace impl {

template <typename T>
  requires std::same_as<T, EpsilonStateBase::Label>
void EpsilonStateBase::print_type(std::ostream &os,
                                  const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::impl::EpsilonStateBase::";
  os << "Label";
}

void EpsilonStateBase::print_value(std::ostream &os, Label label,
                                   const prt::PrintValueArgs &args, uint) {
  print_type<Label>(os, args.print_type_args);
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

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
std::strong_ordering
EpsilonState<_Symbol>::cmp_order_in_state(const EpsilonState &lhs,
                                          const EpsilonState &rhs) {
  return lhs <=> rhs;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
typename EpsilonState<_Symbol>::CmpOrderInState
EpsilonState<_Symbol>::get_cmp_order_in_state() const {
  return cmp_order_in_state;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool EpsilonState<_Symbol>::cmp_less_in_state(const EpsilonState &lhs,
                                              const EpsilonState &rhs) {
  return lhs < rhs;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
typename EpsilonState<_Symbol>::CmpLessInState
EpsilonState<_Symbol>::get_cmp_less_in_state() const {
  return cmp_less_in_state;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void EpsilonState<_Symbol>::print_type(std::ostream &os,
                                       const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "EpsilonState";
  if (args.tmpl_args) {
    os << '<';
    prt::print_type<Symbol>(os, args);
    os << '>';
  }
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void EpsilonState<_Symbol>::print_value(std::ostream &os,
                                        const prt::PrintValueArgs &args,
                                        uint indent_level) const {
  print_type(os, args.print_type_args);
  os << ":\n";
  ++indent_level;
  prt::print_indent(os, indent_level);
  os << "_label:";
  EpsilonStateBase::print_value(os, _label, args, indent_level);
}

} // namespace yao::re::stt

#endif
