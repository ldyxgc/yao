#ifndef __YAO__RE__STT__SYMBOL_STATE__IPP__
#define __YAO__RE__STT__SYMBOL_STATE__IPP__

#include "yao/re/stt/SymbolState.hpp"

#include "yao/def/claim.hpp"

namespace yao::re::stt {

template <typename Symbol>
SymbolState<Symbol>::SymbolState(const Symbol &symbol)
    : _symbol{symbol}, _state{State::START} {}

template <typename Symbol>
std::unique_ptr<SymbolState<Symbol>>
SymbolState<Symbol>::make(const Symbol &symbol) {
  YAO_WARN_PUSH
  YAO_WARN_OFF__DEPRECATED_DECLARATION
  return std::make_unique<SymbolState>(symbol);
  YAO_WARN_POP
}

template <typename Symbol>
void SymbolState<Symbol>::match(const Symbol &symbol) {
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

template <typename Symbol> bool SymbolState<Symbol>::is_final() const {
  return _state == State::FINAL;
}

template <typename Symbol> bool SymbolState<Symbol>::is_dead() const {
  return _state == State::DEAD;
}

} // namespace yao::re::stt

#endif
