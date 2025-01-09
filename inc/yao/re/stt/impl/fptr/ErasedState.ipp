#ifndef __YAO__RE__STT__IMPL__FPTR__ERASED_STATE__IPP__
#define __YAO__RE__STT__IMPL__FPTR__ERASED_STATE__IPP__

#include "yao/re/stt/impl/fptr/ErasedState.hpp"

#include "yao/prt/print_type.hpp"

namespace yao::re::stt::impl::fptr {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState,
          std::enable_if_t<c_r_different_State_with_same_Symbol<
                               ConcreteState, ErasedState<_Symbol>>,
                           int>>
ErasedState<_Symbol>::ErasedState(const ConcreteState &concrete_state)
    : _abstract_state{new ConcreteState{concrete_state}},
      _type_index{typeid(ConcreteState)},

      _fptr__copy_rptr{_sfun__copy_rptr<ConcreteState>},

      _fptr__match{_sfun__match<ConcreteState>},
      _fptr__is_final{_sfun__is_final<ConcreteState>},
      _fptr__is_dead{_sfun__is_dead<ConcreteState>},

      _fptr__equal{_sfun__equal<ConcreteState>},
      _fptr__order{_sfun__order<ConcreteState>},

      _fptr__print_value__false_false{
          _sfun__print_value<ConcreteState, false, false>},
      _fptr__print_value__true_false{
          _sfun__print_value<ConcreteState, true, false>},
      _fptr__print_value__false_true{
          _sfun__print_value<ConcreteState, false, true>},
      _fptr__print_value__true_true{
          _sfun__print_value<ConcreteState, true, true>},

      _fptr__delete{_sfun__delete<ConcreteState>} {}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
ErasedState<_Symbol>::ErasedState(const ErasedState &erased_state)
    : _abstract_state{erased_state._fptr__copy_rptr(
          erased_state._abstract_state)},
      _type_index{erased_state._type_index},

      _fptr__copy_rptr{erased_state._fptr__copy_rptr},

      _fptr__match{erased_state._fptr__match},
      _fptr__is_final{erased_state._fptr__is_final},
      _fptr__is_dead{erased_state._fptr__is_dead},

      _fptr__equal{erased_state._fptr__equal},
      _fptr__order{erased_state._fptr__order},

      _fptr__print_value__false_false{
          erased_state._fptr__print_value__false_false},
      _fptr__print_value__true_false{
          erased_state._fptr__print_value__true_false},
      _fptr__print_value__false_true{
          erased_state._fptr__print_value__false_true},
      _fptr__print_value__true_true{erased_state._fptr__print_value__true_true},

      _fptr__delete{erased_state._fptr__delete} {}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
ErasedState<_Symbol> &ErasedState<_Symbol>::operator=(const ErasedState &rhs) {
  if (_abstract_state == rhs._abstract_state)
    return *this;

  _fptr__delete(_abstract_state);
  _abstract_state = rhs._fptr__copy_rptr(rhs._abstract_state);

  _type_index = rhs._type_index;

  _fptr__copy_rptr = rhs._fptr__copy_rptr;

  _fptr__match = rhs._fptr__match;
  _fptr__is_final = rhs._fptr__is_final;
  _fptr__is_dead = rhs._fptr__is_dead;

  _fptr__equal = rhs._fptr__equal;
  _fptr__order = rhs._fptr__order;

  _fptr__print_value__false_false = rhs._fptr__print_value__false_false;
  _fptr__print_value__true_false = rhs._fptr__print_value__true_false;
  _fptr__print_value__false_true = rhs._fptr__print_value__false_true;
  _fptr__print_value__true_true = rhs._fptr__print_value__true_true;

  _fptr__delete = rhs._fptr__delete;

  return *this;
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
void ErasedState<_Symbol>::match(const Symbol &symbol) {
  _fptr__match(_abstract_state, symbol);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_final() const {
  return _fptr__is_final(_abstract_state);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_dead() const {
  return _fptr__is_dead(_abstract_state);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
bool ErasedState<_Symbol>::operator==(const ErasedState &rhs) const {
  if (_type_index != rhs._type_index)
    return false;
  return _fptr__equal(_abstract_state, rhs._abstract_state);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
auto ErasedState<_Symbol>::operator<=>(const ErasedState &rhs) const {
  if (_type_index != rhs._type_index)
    return _type_index <=> rhs._type_index;
  return _fptr__order(_abstract_state, rhs._abstract_state);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void ErasedState<_Symbol>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::impl::fptr::";
  os << "ErasedState";
  if constexpr (tp) {
    os << '<';
    prt::print_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void ErasedState<_Symbol>::print_value(std::ostream &os) const {
  print_type<ns, tp>(os);
  os << ": {_abstract_state:";
  ns ? (tp ? _fptr__print_value__true_true(_abstract_state, os)
           : _fptr__print_value__true_false(_abstract_state, os))
     : (tp ? _fptr__print_value__false_true(_abstract_state, os)
           : _fptr__print_value__false_false(_abstract_state, os));
  os << '}';
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
ErasedState<_Symbol>::~ErasedState() {
  _fptr__delete(_abstract_state);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
not_null<owner<void *>>
ErasedState<_Symbol>::_sfun__copy_rptr(not_null<void *> abstract_state) {
  return new ConcreteState{*static_cast<ConcreteState *>(abstract_state)};
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
void ErasedState<_Symbol>::_sfun__match(not_null<void *> abstract_state,
                                        const Symbol &symbol) {
  static_cast<ConcreteState *>(abstract_state)->match(symbol);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
bool ErasedState<_Symbol>::_sfun__is_final(not_null<void *> abstract_state) {
  return static_cast<ConcreteState *>(abstract_state)->is_final();
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
bool ErasedState<_Symbol>::_sfun__is_dead(not_null<void *> abstract_state) {
  return static_cast<ConcreteState *>(abstract_state)->is_dead();
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
bool ErasedState<_Symbol>::_sfun__equal(not_null<void *> abstract_state,
                                        not_null<void *> rhs_abstract_state) {
  return (*static_cast<ConcreteState *>(abstract_state)) ==
         (*static_cast<ConcreteState *>(rhs_abstract_state));
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
std::strong_ordering
ErasedState<_Symbol>::_sfun__order(not_null<void *> abstract_state,
                                   not_null<void *> rhs_abstract_state) {
  return (*static_cast<ConcreteState *>(abstract_state)) <=>
         (*static_cast<ConcreteState *>(rhs_abstract_state));
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState, bool ns, bool tp>
void ErasedState<_Symbol>::_sfun__print_value(not_null<void *> abstract_state,
                                              std::ostream &os) {
  static_cast<ConcreteState *>(abstract_state)
      ->template print_value<ns, tp>(os);
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <typename ConcreteState>
void ErasedState<_Symbol>::_sfun__delete(not_null<void *> abstract_state) {
  delete static_cast<ConcreteState *>(abstract_state);
}

} // namespace yao::re::stt::impl::fptr

#endif
