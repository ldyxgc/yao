#ifndef __YAO__RE__STT__IMPL__VTAB__ERASED_STATE__IPP__
#define __YAO__RE__STT__IMPL__VTAB__ERASED_STATE__IPP__

#include "yao/re/stt/impl/vtab/ErasedState.hpp"

#include "yao/prt/osprint_type.hpp"

namespace yao::re::stt::impl::vtab {

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol>::ErasedState(const ErasedState &erased_state)
    : _abstract_state{erased_state._func__copy_rptr(
          erased_state._abstract_state)},
      _func__copy_rptr{erased_state._func__copy_rptr},
      _func__equal{erased_state._func__equal},
      _func__order{erased_state._func__order},
      _func__type{erased_state._func__type},
      _func__match{erased_state._func__match},
      _func__is_final{erased_state._func__is_final},
      _func__is_dead{erased_state._func__is_dead},
      _func__osprint_value__false_false{
          erased_state._func__osprint_value__false_false},
      _func__osprint_value__true_false{
          erased_state._func__osprint_value__true_false},
      _func__osprint_value__false_true{
          erased_state._func__osprint_value__false_true},
      _func__osprint_value__true_true{
          erased_state._func__osprint_value__true_true},
      _func__delete{erased_state._func__delete} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <typename ConcreteState,
          std::enable_if_t<c_r_different_State_with_same_Symbol<
                               ConcreteState, ErasedState<_Symbol>>,
                           int>>
ErasedState<_Symbol>::ErasedState(const ConcreteState &concrete_state)
    : _abstract_state{new ConcreteState{concrete_state}},
      _func__copy_rptr{[](not_null<void *> abstract_state) {
        return new ConcreteState{*static_cast<ConcreteState *>(abstract_state)};
      }},
      _func__equal{[](not_null<void *> abstract_state,
                      not_null<void *> rhs_abstract_state) {
        return (*static_cast<ConcreteState *>(abstract_state)) ==
               (*static_cast<ConcreteState *>(rhs_abstract_state));
      }},
      _func__order{[](not_null<void *> abstract_state,
                      not_null<void *> rhs_abstract_state) {
        return (*static_cast<ConcreteState *>(abstract_state)) <=>
               (*static_cast<ConcreteState *>(rhs_abstract_state));
      }},
      _func__type{[](not_null<void *> abstract_state) {
        return static_cast<ConcreteState *>(abstract_state)->type();
      }},
      _func__match{[](not_null<void *> abstract_state, const Symbol &symbol) {
        static_cast<ConcreteState *>(abstract_state)->match(symbol);
      }},
      _func__is_final{[](not_null<void *> abstract_state) {
        return static_cast<ConcreteState *>(abstract_state)->is_final();
      }},
      _func__is_dead{[](not_null<void *> abstract_state) {
        return static_cast<ConcreteState *>(abstract_state)->is_dead();
      }},
      _func__osprint_value__false_false{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<false, false>(os);
          }},
      _func__osprint_value__true_false{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<true, false>(os);
          }},
      _func__osprint_value__false_true{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<false, true>(os);
          }},
      _func__osprint_value__true_true{
          [](not_null<void *> abstract_state, std::ostream &os) {
            static_cast<ConcreteState *>(abstract_state)
                ->template osprint_value<true, true>(os);
          }},
      _func__delete{[](not_null<void *> abstract_state) {
        delete static_cast<ConcreteState *>(abstract_state);
      }} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol> &ErasedState<_Symbol>::operator=(const ErasedState &rhs) {
  if (_abstract_state == rhs._abstract_state)
    return *this;

  _func__delete(_abstract_state);
  _abstract_state = rhs._func__copy_rptr(rhs._abstract_state);

  _func__copy_rptr = rhs._func__copy_rptr;
  _func__equal = rhs._func__equal;
  _func__order = rhs._func__order;
  _func__type = rhs._func__type;
  _func__match = rhs._func__match;
  _func__is_final = rhs._func__is_final;
  _func__is_dead = rhs._func__is_dead;
  _func__osprint_value__false_false = rhs._func__osprint_value__false_false;
  _func__osprint_value__true_false = rhs._func__osprint_value__true_false;
  _func__osprint_value__false_true = rhs._func__osprint_value__false_true;
  _func__osprint_value__true_true = rhs._func__osprint_value__true_true;
  _func__delete = rhs._func__delete;

  return *this;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::operator==(const ErasedState &rhs) const {
  if (_func__type(_abstract_state) != rhs._func__type(rhs._abstract_state))
    return false;
  return _func__equal(_abstract_state, rhs._abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
auto ErasedState<_Symbol>::operator<=>(const ErasedState &rhs) const {
  if (_func__type(_abstract_state) != rhs._func__type(rhs._abstract_state))
    return _func__type(_abstract_state) <=>
           rhs._func__type(rhs._abstract_state);
  return _func__order(_abstract_state, rhs._abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
StateType ErasedState<_Symbol>::type() const {
  return _func__type(_abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
void ErasedState<_Symbol>::match(const Symbol &symbol) {
  _func__match(_abstract_state, symbol);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_final() const {
  return _func__is_final(_abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool ErasedState<_Symbol>::is_dead() const {
  return _func__is_dead(_abstract_state);
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void ErasedState<_Symbol>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::impl::vtab";
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
  ns ? (tp ? _func__osprint_value__true_true.operator()(_abstract_state, os)
           : _func__osprint_value__true_false.operator()(_abstract_state, os))
     : (tp ? _func__osprint_value__false_true.operator()(_abstract_state, os)
           : _func__osprint_value__false_false.operator()(_abstract_state, os));
  os << '}';
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
ErasedState<_Symbol>::~ErasedState() {
  _func__delete(_abstract_state);
}

} // namespace yao::re::stt::impl::vtab

#endif
