#ifndef __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__IPP__
#define __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__IPP__

#include "yao/re/stt/ConcreteVirtualState.hpp"

#include <typeindex>
#include <utility>

#include "yao/re/stt/ErasedState.hpp"

namespace yao::re::stt {

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
ConcreteVirtualState<ConcreteState>::ConcreteVirtualState(auto &&...args)
    : _concrete_state{std::forward<decltype(args)>(args)...} {}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
not_null<owner<ConcreteVirtualState<ConcreteState> *>>
ConcreteVirtualState<ConcreteState>::make_rptr(auto &&...args) {
  return new ConcreteVirtualState{std::forward<decltype(args)>(args)...};
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
not_null<std::unique_ptr<ConcreteVirtualState<ConcreteState>>>
ConcreteVirtualState<ConcreteState>::make_uptr(auto &&...args) {
  return std::make_unique<ConcreteVirtualState>(
      std::forward<decltype(args)>(args)...);
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
not_null<owner<ConcreteVirtualState<ConcreteState> *>>
ConcreteVirtualState<ConcreteState>::copy_rptr() const {
  return new ConcreteVirtualState{*this};
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
not_null<std::unique_ptr<ConcreteVirtualState<ConcreteState>>>
ConcreteVirtualState<ConcreteState>::copy_uptr() const {
  return std::make_unique<ConcreteVirtualState>(*this);
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
void ConcreteVirtualState<ConcreteState>::match(const Symbol &symbol) {
  _concrete_state.match(symbol);
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::is_final() const {
  return _concrete_state.is_final();
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::is_dead() const {
  return _concrete_state.is_dead();
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::operator==(
    const ConcreteVirtualState &rhs) const {
  return _concrete_state == rhs._concrete_state;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
auto ConcreteVirtualState<ConcreteState>::operator<=>(
    const ConcreteVirtualState &rhs) const {
  return _concrete_state <=> rhs._concrete_state;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
template <typename OtherConcreteState>
  requires req::c_r_no_cvref<OtherConcreteState> &&
           c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                ConcreteState>
bool ConcreteVirtualState<ConcreteState>::operator==(
    const ConcreteVirtualState<OtherConcreteState> &) const {
  return false;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
template <typename OtherConcreteState>
  requires req::c_r_no_cvref<OtherConcreteState> &&
           c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                ConcreteState>
auto ConcreteVirtualState<ConcreteState>::operator<=>(
    const ConcreteVirtualState<OtherConcreteState> &) const {
  return std::type_index{typeid(ConcreteState)} <=>
         std::type_index{typeid(OtherConcreteState)};
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::operator==(
    const VirtualState<Symbol> &rhs) const {
  auto that = dynamic_cast<const ConcreteVirtualState *>(&rhs);
  if (that == nullptr)
    return false;
  return _concrete_state == that->_concrete_state;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
std::strong_ordering ConcreteVirtualState<ConcreteState>::operator<=>(
    const VirtualState<Symbol> &rhs) const {
  auto that = dynamic_cast<const ConcreteVirtualState *>(&rhs);
  if (that == nullptr)
    return std::type_index{typeid(*this)} <=> std::type_index{typeid(rhs)};
  return _concrete_state <=> that->_concrete_state;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::cmp_less1_assume_same_known_type(
    const VirtualState<Symbol> &lhs, const VirtualState<Symbol> &rhs) {
  auto lhs_concrete_virtual_state =
      static_cast<const ConcreteVirtualState *>(&lhs);
  auto rhs_concrete_virtual_state =
      static_cast<const ConcreteVirtualState *>(&rhs);
  return lhs_concrete_virtual_state->_concrete_state <
         rhs_concrete_virtual_state->_concrete_state;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
typename ConcreteVirtualState<ConcreteState>::CmpLess1
ConcreteVirtualState<ConcreteState>::get_cmp_less1_assume_same_known_type()
    const {
  return cmp_less1_assume_same_known_type;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
bool ConcreteVirtualState<ConcreteState>::cmp_less2_assume_same_known_type(
    const ErasedState<Symbol> &lhs, const ErasedState<Symbol> &rhs) {
  auto lhs_concrete_virtual_state =
      static_cast<const ConcreteVirtualState *>(lhs.get());
  auto rhs_concrete_virtual_state =
      static_cast<const ConcreteVirtualState *>(rhs.get());
  return lhs_concrete_virtual_state->_concrete_state <
         rhs_concrete_virtual_state->_concrete_state;
}

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
typename ConcreteVirtualState<ConcreteState>::CmpLess2
ConcreteVirtualState<ConcreteState>::get_cmp_less2_assume_same_known_type()
    const {
  return cmp_less2_assume_same_known_type;
}

} // namespace yao::re::stt

#endif
