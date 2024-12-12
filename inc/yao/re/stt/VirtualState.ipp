#ifndef __YAO__RE__STT__VIRTUAL_STATE__IPP__
#define __YAO__RE__STT__VIRTUAL_STATE__IPP__

#include "yao/re/stt/VirtualState.hpp"

#include "yao/prt/osprint_type.hpp"
#include "yao/prt/osprint_value.hpp"

namespace yao::re::stt {

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
VirtualState<ConcreteState>::VirtualState(const auto &...args)
    : _concrete_state{args...} {}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
not_null<owner<VirtualState<ConcreteState> *>>
VirtualState<ConcreteState>::make_rptr(const auto &...args) {
  return new VirtualState{args...};
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
not_null<std::unique_ptr<VirtualState<ConcreteState>>>
VirtualState<ConcreteState>::make_uptr(const auto &...args) {
  return std::make_unique<VirtualState>(args...);
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
not_null<owner<VirtualState<ConcreteState> *>>
VirtualState<ConcreteState>::copy_rptr() const {
  return new VirtualState{*this};
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
not_null<std::unique_ptr<VirtualState<ConcreteState>>>
VirtualState<ConcreteState>::copy_uptr() const {
  return std::make_unique<VirtualState>(*this);
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
bool VirtualState<ConcreteState>::operator==(const VirtualState &rhs) const {
  return _concrete_state == rhs._concrete_state;
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
auto VirtualState<ConcreteState>::operator<=>(const VirtualState &rhs) const {
  return _concrete_state <=> rhs._concrete_state;
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
template <typename OtherConcreteState>
  requires c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                ConcreteState>
bool VirtualState<ConcreteState>::operator==(
    const VirtualState<OtherConcreteState> &) const {
  return false;
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
template <typename OtherConcreteState>
  requires c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                ConcreteState>
auto VirtualState<ConcreteState>::operator<=>(
    const VirtualState<OtherConcreteState> &rhs) const {
  return type() <=> rhs.type();
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
bool VirtualState<ConcreteState>::operator==(
    const VirtualStateBase<Symbol> &rhs) const {
  auto that = dynamic_cast<const VirtualState *>(&rhs);
  if (that == nullptr)
    return false;
  return _concrete_state == that->_concrete_state;
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
std::strong_ordering VirtualState<ConcreteState>::operator<=>(
    const VirtualStateBase<Symbol> &rhs) const {
  auto that = dynamic_cast<const VirtualState *>(&rhs);
  if (that == nullptr)
    return type() <=> rhs.type();
  return _concrete_state <=> that->_concrete_state;
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
StateType VirtualState<ConcreteState>::type() const {
  return _concrete_state.type();
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
void VirtualState<ConcreteState>::match(const Symbol &symbol) {
  _concrete_state.match(symbol);
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
bool VirtualState<ConcreteState>::is_final() const {
  return _concrete_state.is_final();
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
bool VirtualState<ConcreteState>::is_dead() const {
  return _concrete_state.is_dead();
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
template <bool ns, bool tp>
void VirtualState<ConcreteState>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "VirtualState";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<ConcreteState, ns, tp>(os);
    os << '>';
  }
}

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
void VirtualState<ConcreteState>::osprint_value(std::ostream &os, bool ns,
                                                bool tp) const {
  ns ? (tp ? prt::osprint_type<VirtualState, true, true>(os)
           : prt::osprint_type<VirtualState, true>(os))
     : (tp ? prt::osprint_type<VirtualState, false, true>(os)
           : prt::osprint_type<VirtualState>(os));
  os << ": {_concrete_state:";
  ns ? (tp ? prt::osprint_value<true, true>(os, _concrete_state)
           : prt::osprint_value<true>(os, _concrete_state))
     : (tp ? prt::osprint_value<false, true>(os, _concrete_state)
           : prt::osprint_value<>(os, _concrete_state));
  os << '}';
}

} // namespace yao::re::stt

#endif
