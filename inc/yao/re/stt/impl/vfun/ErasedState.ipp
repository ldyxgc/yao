#ifndef __YAO__RE__STT__IMPL__VFUN__ERASED_STATE__IPP__
#define __YAO__RE__STT__IMPL__VFUN__ERASED_STATE__IPP__

#include "yao/re/stt/impl/vfun/ErasedState.hpp"

#include "yao/prt/osprint_type.hpp"
#include "yao/prt/osprint_value.hpp"
#include "yao/re/stt/VirtualState.hpp"

namespace yao::re::stt::impl::vfun {

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol>::ErasedState(const ErasedState &erased_state)
    : _virtual_state{erased_state._virtual_state->copy_uptr()} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <typename ConcreteState,
          std::enable_if_t<c_r_different_State_with_same_Symbol<
                               ConcreteState, ErasedState<_Symbol>>,
                           int>>
ErasedState<_Symbol>::ErasedState(const ConcreteState &concrete_state)
    : _virtual_state{VirtualState<ConcreteState>::make_uptr(concrete_state)} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol> &ErasedState<_Symbol>::operator=(const ErasedState &rhs) {
  _virtual_state = rhs._virtual_state->copy_uptr();
  return *this;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::operator==(const ErasedState &rhs) const {
  return *_virtual_state == *rhs._virtual_state;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
auto ErasedState<_Symbol>::operator<=>(const ErasedState &rhs) const {
  return *_virtual_state <=> *rhs._virtual_state;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
StateType ErasedState<_Symbol>::type() const {
  return _virtual_state->type();
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
void ErasedState<_Symbol>::match(const Symbol &symbol) {
  _virtual_state->match(symbol);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_final() const {
  return _virtual_state->is_final();
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_dead() const {
  return _virtual_state->is_dead();
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void ErasedState<_Symbol>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::impl::vfun";
  os << "ErasedState";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void ErasedState<_Symbol>::osprint_value(std::ostream &os) const {
  prt::osprint_type<ErasedState, ns, tp>(os);
  os << ": {_virtual_state:";
  prt::osprint_value<ns, tp>(os, _virtual_state);
  os << '}';
}

} // namespace yao::re::stt::impl::vfun

#endif
