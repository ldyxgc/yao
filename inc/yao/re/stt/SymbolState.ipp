#ifndef __YAO__RE__STT__SYMBOL_STATE__IPP__
#define __YAO__RE__STT__SYMBOL_STATE__IPP__

#include "yao/re/stt/SymbolState.hpp"

#include <utility>

#include "yao/def/claim.hpp"
#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

namespace impl {

template <typename T>
  requires std::same_as<T, SymbolStateBase::Label>
void SymbolStateBase::print_type(std::ostream &os,
                                 const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::impl::SymbolStateBase::";
  os << "Label";
}

void SymbolStateBase::print_value(std::ostream &os, Label label,
                                  const prt::PrintValueArgs &args, uint) {
  print_type<Label>(os, args.print_type_args);
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
  requires c_r_no_cvref_Symbol<_Symbol>
template <typename __Symbol>
  requires c_ct_Symbol<std::remove_cvref_t<__Symbol>>
SymbolState<_Symbol>::SymbolState(__Symbol &&symbol)
    : _symbol{std::forward<__Symbol>(symbol)}, _label{Label::START} {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
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
  requires c_r_no_cvref_Symbol<_Symbol>
bool SymbolState<_Symbol>::is_final() const {
  return _label == Label::FINAL;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool SymbolState<_Symbol>::is_dead() const {
  return _label == Label::DEAD;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void SymbolState<_Symbol>::print_type(std::ostream &os,
                                      const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "SymbolState";
  if (args.tmpl_args) {
    os << '<';
    prt::print_type<Symbol>(os, args);
    os << '>';
  }
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void SymbolState<_Symbol>::print_value(std::ostream &os,
                                       const prt::PrintValueArgs &args,
                                       uint indent_level) const {
  print_type(os, args.print_type_args);
  os << ":\n";
  ++indent_level;
  prt::print_indent(os, indent_level);
  os << "_symbol:";
  prt::print_value(os, _symbol, args, indent_level);
  os << '\n';
  prt::print_indent(os, indent_level);
  os << "_label:";
  SymbolStateBase::print_value(os, _label, args, indent_level);
}

} // namespace yao::re::stt

#endif
