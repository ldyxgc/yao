#ifndef __YAO__LAB__RE__STT__SYMBOL_STATE__IPP__
#define __YAO__LAB__RE__STT__SYMBOL_STATE__IPP__

#include "yao/lab/re/stt/SymbolState.hpp"

#include "yao/def/claim.hpp"
#include "yao/lab/prt/osprint_type.hpp"
#include "yao/lab/prt/osprint_value.hpp"

namespace yao::lab::re::stt {

namespace impl {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, SymbolStateBase::State>
void SymbolStateBase::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::lab::re::stt::impl::SymbolStateBase::";
  os << "State";
}

template <bool ns, bool tp>
void SymbolStateBase::osprint_value(std::ostream &os, State state) {
  osprint_type<State, ns, tp>(os);
  os << ": ";
  switch (state) {
  case State::START:
    os << "START";
    break;
  case State::FINAL:
    os << "FINAL";
    break;
  case State::DEAD:
    os << "DEAD";
    break;
  default:
    YAO_CLAIM(false);
    break;
  }
}

} // namespace impl

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
SymbolState<_Symbol>::SymbolState(const Symbol &symbol)
    : _symbol{symbol}, _state{State::START} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
StateType SymbolState<_Symbol>::type() const {
  return StateType::SymbolState;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
void SymbolState<_Symbol>::match(const Symbol &symbol) {
  switch (_state) {
  case State::START:
    _state = _symbol == symbol ? State::FINAL : State::DEAD;
    break;
  case State::FINAL:
    _state = State::DEAD;
    break;
  case State::DEAD:
    break;
  default:
    YAO_CLAIM(false);
    break;
  }
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool SymbolState<_Symbol>::is_final() const {
  return _state == State::FINAL;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool SymbolState<_Symbol>::is_dead() const {
  return _state == State::DEAD;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void SymbolState<_Symbol>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::lab::re::stt::";
  os << "SymbolState";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void SymbolState<_Symbol>::osprint_value(std::ostream &os) const {
  prt::osprint_type<SymbolState, ns, tp>(os);
  os << ": {_symbol:";
  prt::osprint_value<ns, tp>(os, _symbol);
  os << ",_state:";
  SymbolStateBase::osprint_value<ns, tp>(os, _state);
  os << '}';
}

} // namespace yao::lab::re::stt

#endif
