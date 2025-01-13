#ifndef __YAO__RE__STT__ERASED_STATE__IPP__
#define __YAO__RE__STT__ERASED_STATE__IPP__

#include "yao/re/stt/ErasedState.hpp"

#include <utility>

#include "yao/re/stt/ConcreteVirtualState.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
template <typename ConcreteState,
          std::enable_if_t<
              c_r_different_State_with_same_Symbol<
                  std::remove_cvref_t<ConcreteState>, ErasedState<_Symbol>>,
              int>>
ErasedState<_Symbol>::ErasedState(ConcreteState &&concrete_state)
    : _virtual_state{
          ConcreteVirtualState<std::remove_cvref_t<ConcreteState>>::make_uptr(
              std::forward<ConcreteState>(concrete_state))} {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
template <typename ConcreteState>
  requires c_ct_State<std::remove_cvref_t<ConcreteState>>
ErasedState<_Symbol>::ErasedState(ConcreteState &&concrete_state, int)
    : _virtual_state{
          ConcreteVirtualState<std::remove_cvref_t<ConcreteState>>::make_uptr(
              std::forward<ConcreteState>(concrete_state))} {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
ErasedState<_Symbol>::ErasedState(const ErasedState &erased_state)
    : _virtual_state{erased_state._virtual_state->copy_uptr()} {}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
ErasedState<_Symbol> &
ErasedState<_Symbol>::operator=(const ErasedState &erased_state) {
  _virtual_state = erased_state._virtual_state->copy_uptr();
  return *this;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void ErasedState<_Symbol>::match(const Symbol &symbol) {
  _virtual_state->match(symbol);
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_final() const {
  return _virtual_state->is_final();
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_dead() const {
  return _virtual_state->is_dead();
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
bool ErasedState<_Symbol>::operator==(const ErasedState &rhs) const {
  return *_virtual_state == *rhs._virtual_state;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
auto ErasedState<_Symbol>::operator<=>(const ErasedState &rhs) const {
  return *_virtual_state <=> *rhs._virtual_state;
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
typename ErasedState<_Symbol>::CmpLess1
ErasedState<_Symbol>::get_cmp_less1_assume_same_known_type() const {
  return {_virtual_state->get_cmp_less1_assume_same_known_type()};
}

} // namespace yao::re::stt

#endif
