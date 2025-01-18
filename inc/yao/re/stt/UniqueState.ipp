#ifndef __YAO__RE__STT__UNIQUE_STATE__IPP__
#define __YAO__RE__STT__UNIQUE_STATE__IPP__

#include "yao/re/stt/UniqueState.hpp"

#include <utility>

#include "yao/prt/print_indent.hpp"
#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
UniqueState<_Symbol>::UniqueState(
    std::unique_ptr<VirtualState<Symbol>> &&virtual_state)
    : _virtual_state{std::move(virtual_state)} {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
UniqueState<_Symbol>::UniqueState(const UniqueState &unique_state)
    : _virtual_state{unique_state._virtual_state->copy_uptr()} {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
UniqueState<_Symbol> &
UniqueState<_Symbol>::operator=(const UniqueState &unique_state) {
  _virtual_state = unique_state._virtual_state->copy_uptr();
  return *this;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void UniqueState<_Symbol>::match(const Symbol &symbol) {
  _virtual_state->match(symbol);
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool UniqueState<_Symbol>::is_final() const {
  return _virtual_state->is_final();
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool UniqueState<_Symbol>::is_dead() const {
  return _virtual_state->is_dead();
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool UniqueState<_Symbol>::operator==(const UniqueState &rhs) const {
  return *_virtual_state == *rhs._virtual_state;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
auto UniqueState<_Symbol>::operator<=>(const UniqueState &rhs) const {
  return *_virtual_state <=> *rhs._virtual_state;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
typename UniqueState<_Symbol>::CmpLessInState
UniqueState<_Symbol>::get_cmp_less_in_state() const {
  return CmpLessInState{_virtual_state->get_cmp_less_in_state()};
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void UniqueState<_Symbol>::print_type(std::ostream &os,
                                      const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "UniqueState";
  if (args.tmpl_args) {
    os << '<';
    prt::print_type<Symbol>(os, args);
    os << '>';
  }
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void UniqueState<_Symbol>::print_value(std::ostream &os,
                                       const prt::PrintValueArgs &args,
                                       uint indent_level) const {
  print_type(os, args.print_type_args);
  os << ":\n";
  ++indent_level;
  prt::print_indent(os, indent_level);
  os << "_virtual_state:";
  prt::print_value(os, _virtual_state, args, indent_level);
}

} // namespace yao::re::stt

#endif
