#ifndef __YAO__RE__STT__IMPL__FOBJ__ERASED_STATE__IPP__
#define __YAO__RE__STT__IMPL__FOBJ__ERASED_STATE__IPP__

#include "yao/re/stt/impl/fobj/ErasedState.hpp"

#include "yao/prt/osprint_type.hpp"

namespace yao::re::stt::impl::fobj {

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol>::ErasedState(const ErasedState &erased_state)
    : _abstract_state{erased_state._fobj__copy_rptr(
          erased_state._abstract_state)},
      _fobj__copy_rptr{erased_state._fobj__copy_rptr},
      _fobj__equal{erased_state._fobj__equal},
      _fobj__order{erased_state._fobj__order},
      _fobj__type{erased_state._fobj__type},
      _fobj__match{erased_state._fobj__match},
      _fobj__is_final{erased_state._fobj__is_final},
      _fobj__is_dead{erased_state._fobj__is_dead},
      _fobj__osprint_value__false_false{
          erased_state._fobj__osprint_value__false_false},
      _fobj__osprint_value__true_false{
          erased_state._fobj__osprint_value__true_false},
      _fobj__osprint_value__false_true{
          erased_state._fobj__osprint_value__false_true},
      _fobj__osprint_value__true_true{
          erased_state._fobj__osprint_value__true_true},
      _fobj__delete{erased_state._fobj__delete} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <typename ConcreteState,
          std::enable_if_t<c_r_different_State_with_same_Symbol<
                               ConcreteState, ErasedState<_Symbol>>,
                           int>>
ErasedState<_Symbol>::ErasedState(const ConcreteState &concrete_state)
    : _abstract_state{new ConcreteState{concrete_state}},
      _fobj__copy_rptr{[](not_null<void *> abstract_state) {
        return new ConcreteState{*static_cast<ConcreteState *>(abstract_state)};
      }},
      _fobj__equal{[](not_null<void *> abstract_state,
                      not_null<void *> rhs_abstract_state) {
        return (*static_cast<ConcreteState *>(abstract_state)) ==
               (*static_cast<ConcreteState *>(rhs_abstract_state));
      }},
      _fobj__order{[](not_null<void *> abstract_state,
                      not_null<void *> rhs_abstract_state) {
        return (*static_cast<ConcreteState *>(abstract_state)) <=>
               (*static_cast<ConcreteState *>(rhs_abstract_state));
      }},
      _fobj__type{[](not_null<void *> abstract_state) {
        return static_cast<ConcreteState *>(abstract_state)->type();
      }},
      _fobj__match{[](not_null<void *> abstract_state, const Symbol &symbol) {
        static_cast<ConcreteState *>(abstract_state)->match(symbol);
      }},
      _fobj__is_final{[](not_null<void *> abstract_state) {
        return static_cast<ConcreteState *>(abstract_state)->is_final();
      }},
      _fobj__is_dead{[](not_null<void *> abstract_state) {
        return static_cast<ConcreteState *>(abstract_state)->is_dead();
      }},
      _fobj__osprint_value__false_false{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<false, false>(os);
          }},
      _fobj__osprint_value__true_false{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<true, false>(os);
          }},
      _fobj__osprint_value__false_true{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<false, true>(os);
          }},
      _fobj__osprint_value__true_true{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<true, true>(os);
          }},
      _fobj__delete{[](not_null<void *> abstract_state) {
        delete static_cast<ConcreteState *>(abstract_state);
      }} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol> &ErasedState<_Symbol>::operator=(const ErasedState &rhs) {
  if (_abstract_state == rhs._abstract_state)
    return *this;

  _fobj__delete(_abstract_state);
  _abstract_state = rhs._fobj__copy_rptr(rhs._abstract_state);

  _fobj__copy_rptr = rhs._fobj__copy_rptr;
  _fobj__equal = rhs._fobj__equal;
  _fobj__order = rhs._fobj__order;
  _fobj__type = rhs._fobj__type;
  _fobj__match = rhs._fobj__match;
  _fobj__is_final = rhs._fobj__is_final;
  _fobj__is_dead = rhs._fobj__is_dead;
  _fobj__osprint_value__false_false = rhs._fobj__osprint_value__false_false;
  _fobj__osprint_value__true_false = rhs._fobj__osprint_value__true_false;
  _fobj__osprint_value__false_true = rhs._fobj__osprint_value__false_true;
  _fobj__osprint_value__true_true = rhs._fobj__osprint_value__true_true;
  _fobj__delete = rhs._fobj__delete;

  return *this;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::operator==(const ErasedState &rhs) const {
  if (_fobj__type(_abstract_state) != rhs._fobj__type(rhs._abstract_state))
    return false;
  return _fobj__equal(_abstract_state, rhs._abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
auto ErasedState<_Symbol>::operator<=>(const ErasedState &rhs) const {
  if (_fobj__type(_abstract_state) != rhs._fobj__type(rhs._abstract_state))
    return _fobj__type(_abstract_state) <=>
           rhs._fobj__type(rhs._abstract_state);
  return _fobj__order(_abstract_state, rhs._abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
StateType ErasedState<_Symbol>::type() const {
  return _fobj__type(_abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
void ErasedState<_Symbol>::match(const Symbol &symbol) {
  _fobj__match(_abstract_state, symbol);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_final() const {
  return _fobj__is_final(_abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_dead() const {
  return _fobj__is_dead(_abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void ErasedState<_Symbol>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::impl::fobj";
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
  os << ": {_abstract_state:";
  ns ? (tp ? _fobj__osprint_value__true_true(_abstract_state, os)
           : _fobj__osprint_value__true_false(_abstract_state, os))
     : (tp ? _fobj__osprint_value__false_true(_abstract_state, os)
           : _fobj__osprint_value__false_false(_abstract_state, os));
  os << '}';
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol>::~ErasedState() {
  _fobj__delete(_abstract_state);
}

} // namespace yao::re::stt::impl::fobj

#endif
