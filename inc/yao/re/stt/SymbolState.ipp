#ifndef __YAO__RE__STT__SYMBOL_STATE__IPP__
#define __YAO__RE__STT__SYMBOL_STATE__IPP__

#include "yao/re/stt/SymbolState.hpp"

#include <utility>

#include "yao/def/claim.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

namespace impl {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, SymbolStateBase::Label>
void SymbolStateBase::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::impl::SymbolStateBase::";
  os << "Label";
}

template <bool ns, bool tp>
void SymbolStateBase::print_value(std::ostream &os, Label label) {
  print_type<Label, ns, tp>(os);
  os << ": ";
  switch (label) {
  case Label::START:
    os << "START";
    break;
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
SymbolState<_Symbol>::SymbolState(const Symbol &symbol)
    : _symbol{symbol}, _label{Label::START} {}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
SymbolState<_Symbol>::SymbolState(Symbol &&symbol)
    : _symbol{std::move(symbol)}, _label{Label::START} {}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
void SymbolState<_Symbol>::match(const Symbol &symbol) {
  switch (_label) {
  case Label::START:
    _label = _symbol == symbol ? Label::FINAL : Label::DEAD;
    break;
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
bool SymbolState<_Symbol>::is_final() const {
  return _label == Label::FINAL;
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
bool SymbolState<_Symbol>::is_dead() const {
  return _label == Label::DEAD;
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void SymbolState<_Symbol>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "SymbolState";
  if constexpr (tp) {
    os << '<';
    prt::print_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void SymbolState<_Symbol>::print_value(std::ostream &os) const {
  print_type<ns, tp>(os);
  os << ": {_symbol:";
  prt::print_value<ns, tp>(os, _symbol);
  os << ",_label:";
  SymbolStateBase::print_value<ns, tp>(os, _label);
  os << '}';
}

} // namespace yao::re::stt

#endif
