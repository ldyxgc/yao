#ifndef __YAO__LAB__RE__STT__EPSILON_STATE__IPP__
#define __YAO__LAB__RE__STT__EPSILON_STATE__IPP__

#include "yao/lab/re/stt/EpsilonState.hpp"

#include "yao/def/claim.hpp"
#include "yao/lab/prt/osprint_type.hpp"

namespace yao::lab::re::stt {

namespace impl {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, EpsilonStateBase::State>
void EpsilonStateBase::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::lab::re::stt::impl::EpsilonStateBase::";
  os << "State";
}

template <bool ns, bool tp>
void EpsilonStateBase::osprint_value(std::ostream &os, State state) {
  osprint_type<State, ns, tp>(os);
  os << ": ";
  switch (state) {
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
EpsilonState<_Symbol>::EpsilonState() : _state{State::FINAL} {}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
StateType EpsilonState<_Symbol>::type() const {
  return StateType::EpsilonState;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
void EpsilonState<_Symbol>::match(const Symbol &) {
  switch (_state) {
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
bool EpsilonState<_Symbol>::is_final() const {
  return _state == State::FINAL;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
bool EpsilonState<_Symbol>::is_dead() const {
  return _state == State::DEAD;
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void EpsilonState<_Symbol>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::lab::re::stt::";
  os << "EpsilonState";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
template <bool ns, bool tp>
void EpsilonState<_Symbol>::osprint_value(std::ostream &os) const {
  prt::osprint_type<EpsilonState, ns, tp>(os);
  os << ": {_state:";
  EpsilonStateBase::osprint_value<ns, tp>(os, _state);
  os << '}';
}

} // namespace yao::lab::re::stt

#endif
