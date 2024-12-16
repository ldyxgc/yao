#ifndef __YAO__RE__STT__EPSILON_STATE__IPP__
#define __YAO__RE__STT__EPSILON_STATE__IPP__

#include "yao/re/stt/EpsilonState.hpp"

#include "yao/def/claim.hpp"

namespace yao::re::stt {

template <typename Symbol>
EpsilonState<Symbol>::EpsilonState() : _state{State::FINAL} {}

template <typename Symbol>
std::unique_ptr<EpsilonState<Symbol>> EpsilonState<Symbol>::make() {
  return std::make_unique<EpsilonState>();
}

template <typename Symbol> void EpsilonState<Symbol>::match(const Symbol &) {
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

template <typename Symbol> bool EpsilonState<Symbol>::is_final() const {
  return _state == State::FINAL;
}

template <typename Symbol> bool EpsilonState<Symbol>::is_dead() const {
  return _state == State::DEAD;
}

} // namespace yao::re::stt

#endif
