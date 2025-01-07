#ifndef __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__IPP__
#define __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__IPP__

#include "yao/re/stt/ConcreteVirtualState.hpp"

#include <typeindex>
#include <utility>

#include "yao/prt/print_type.hpp"
#include "yao/prt/print_value.hpp"

namespace yao::re::stt {

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
ConcreteVirtualState<ConcreteState>::ConcreteVirtualState(auto &&...args)
    : _concrete_state{std::forward<decltype(args)>(args)...} {}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
not_null<owner<ConcreteVirtualState<ConcreteState> *>>
ConcreteVirtualState<ConcreteState>::make_rptr(auto &&...args) {
  return new ConcreteVirtualState{std::forward<decltype(args)>(args)...};
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
not_null<std::unique_ptr<ConcreteVirtualState<ConcreteState>>>
ConcreteVirtualState<ConcreteState>::make_uptr(auto &&...args) {
  return std::make_unique<ConcreteVirtualState>(
      std::forward<decltype(args)>(args)...);
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
not_null<owner<ConcreteVirtualState<ConcreteState> *>>
ConcreteVirtualState<ConcreteState>::copy_rptr() const {
  return new ConcreteVirtualState{*this};
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
not_null<std::unique_ptr<ConcreteVirtualState<ConcreteState>>>
ConcreteVirtualState<ConcreteState>::copy_uptr() const {
  return std::make_unique<ConcreteVirtualState>(*this);
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
void ConcreteVirtualState<ConcreteState>::match(const Symbol &symbol) {
  _concrete_state.match(symbol);
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::is_final() const {
  return _concrete_state.is_final();
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::is_dead() const {
  return _concrete_state.is_dead();
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::operator==(
    const ConcreteVirtualState &rhs) const {
  return _concrete_state == rhs._concrete_state;
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
auto ConcreteVirtualState<ConcreteState>::operator<=>(
    const ConcreteVirtualState &rhs) const {
  return _concrete_state <=> rhs._concrete_state;
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> &&
           c_ct_State<ConcreteState>
           template <typename OtherConcreteState>
             requires req::c_r_no_cvref<OtherConcreteState> &&
                      c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                           ConcreteState>
bool ConcreteVirtualState<ConcreteState>::operator==(
    const ConcreteVirtualState<OtherConcreteState> &) const {
  return false;
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> &&
           c_ct_State<ConcreteState>
           template <typename OtherConcreteState>
             requires req::c_r_no_cvref<OtherConcreteState> &&
                      c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                           ConcreteState>
auto ConcreteVirtualState<ConcreteState>::operator<=>(
    const ConcreteVirtualState<OtherConcreteState> &rhs) const {
  return std::type_index{typeid(*this)} <=> std::type_index{typeid(rhs)};
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::operator==(
    const VirtualState<Symbol> &rhs) const {
  auto that = dynamic_cast<const ConcreteVirtualState *>(&rhs);
  if (that == nullptr)
    return false;
  return _concrete_state == that->_concrete_state;
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
std::strong_ordering ConcreteVirtualState<ConcreteState>::operator<=>(
    const VirtualState<Symbol> &rhs) const {
  auto that = dynamic_cast<const ConcreteVirtualState *>(&rhs);
  if (that == nullptr)
    return std::type_index{typeid(*this)} <=> std::type_index{typeid(rhs)};
  return _concrete_state <=> that->_concrete_state;
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
template <bool ns, bool tp>
void ConcreteVirtualState<ConcreteState>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "ConcreteVirtualState";
  if constexpr (tp) {
    os << '<';
    prt::print_type<ConcreteState, ns, tp>(os);
    os << '>';
  }
}

template <typename ConcreteState>
  requires req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>
void ConcreteVirtualState<ConcreteState>::print_value(std::ostream &os, bool ns,
                                                      bool tp) const {
  ns ? (tp ? print_type<true, true>(os) : print_type<true>(os))
     : (tp ? print_type<false, true>(os) : print_type<>(os));
  os << ": {_concrete_state:";
  ns ? (tp ? prt::print_value<true, true>(os, _concrete_state)
           : prt::print_value<true>(os, _concrete_state))
     : (tp ? prt::print_value<false, true>(os, _concrete_state)
           : prt::print_value<>(os, _concrete_state));
  os << '}';
}

} // namespace yao::re::stt

#endif
